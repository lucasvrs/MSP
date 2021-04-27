/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "tilefactory.h"
#include "Xml/xmlreader.h"
#include "Xml/xmlwriter.h"
#include "tileitem.h"
#include "previewtilefactory.h"
#include <QDomDocument>

TileFactory::TileFactory()
{
    m_reader = new XMLReader("./../FinalMsp/Config/tileconfig.xml");
    m_writer = new XMLWriter("./../FinalMsp/Config/tileconfig.xml");
    m_previewFactory = new PreviewTileFactory;
}

QList<TileItem*> TileFactory::tiles()
{
    m_reader = new XMLReader("./../FinalMsp/Config/tileconfig.xml");
    m_writer = new XMLWriter("./../FinalMsp/Config/tileconfig.xml");
    QList<TileItem*> tiles;
    for(QDomElement e : *m_reader->allElemsUnderRoot())
    {
        TileItem* tile = new TileItem;
        //XMLNameConverter conv(e.tagName());
        //tile->setText(conv.convertedName());
        tile->setText(e.tagName());
        tile->setId(e.attribute("id").toInt());
        QDomElement color = m_reader->findElemUnderElem(e, "color");
        QList<QDomElement> values = *m_reader->allElemsUnderElem(color);
        tile->setColor(QColor(values[0].text().toInt(), values[1].text().toInt(), values[2].text().toInt(), values[3].text().toInt()));
        QDomElement textColor = m_reader->findElemUnderElem(e, "textcolor");
        values = *m_reader->allElemsUnderElem(textColor);
        tile->setTextColor(QColor(values[0].text().toInt(), values[1].text().toInt(), values[2].text().toInt(), values[3].text().toInt()));
        QDomElement apps = m_reader->findElemUnderElem(e, "apps");
        QList<TileItem*> list;
        for(QDomElement e : *m_reader->allElemsUnderElem(apps))
        {
            TileItem* preview = m_previewFactory->tile(e.text());
            if(tile != nullptr) list.append(preview);
        }
        tile->setPreviews(list);
        tiles.append(tile);
    }
    return tiles;
}

void TileFactory::createTile(const QString& name, const QColor& color, const QColor& textColor)
{
    QDomElement e = *m_writer->getRootElement();
    QDomElement tile = m_writer->createElement(name);
    tile.setAttribute("id", m_reader->allElemsUnderRoot()->size() + 1);
    m_writer->appendElementUnderElement(e, tile);
    QDomElement tileColor = m_writer->createElement("color");
    QDomElement tileTextColor = m_writer->createElement("textcolor");
    m_writer->appendElementUnderElement(tile, tileColor);
    m_writer->appendElementUnderElement(tileColor, "r", QString::number(color.red()));
    m_writer->appendElementUnderElement(tileColor, "g", QString::number(color.green()));
    m_writer->appendElementUnderElement(tileColor, "b", QString::number(color.blue()));
    m_writer->appendElementUnderElement(tileColor, "a", QString::number(color.alpha()));
    m_writer->appendElementUnderElement(tile, tileTextColor);
    m_writer->appendElementUnderElement(tileTextColor, "r", QString::number(textColor.red()));
    m_writer->appendElementUnderElement(tileTextColor, "g", QString::number(textColor.green()));
    m_writer->appendElementUnderElement(tileTextColor, "b", QString::number(textColor.blue()));
    m_writer->appendElementUnderElement(tileTextColor, "a", QString::number(textColor.alpha()));
    m_writer->appendElementUnderElement(tile, "apps");
    m_writer->saveXML();
}

void TileFactory::deleteTile(const QString &name, int id)
{
    //QDomElement e = *m_writer->getRootElement();
    m_writer->removeElement(name, "id", id);
    m_writer->saveXML();
}

void TileFactory::deletePreviewTile(const QString& title, int collectionId, const QString &name, int id)
{
    QDomElement subjectElem = m_writer->getElementUnderRoot(title, "id", collectionId);
    QDomElement elem = m_writer->getTileElement(subjectElem, "app", name, "id", id);
    m_writer->removeElement(elem);
    m_writer->saveXML();
}

void TileFactory::addAppToTile(const QString &name, int id, const QString& appName, int appId)
{
    QDomElement e = m_writer->getElement(name, "id", id);
    QDomElement app = m_writer->getElementUnderElement(e, "apps");
    m_writer->appendElementUnderElement(app, "app", appName, "id", appId);
    m_writer->saveXML();
}
