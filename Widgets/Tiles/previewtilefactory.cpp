/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "previewtilefactory.h"
#include "Xml/xmlreader.h"
#include "tileitem.h"
#include "widgetfactory.h"
#include <QDomDocument>
#include <QDebug>

PreviewTileFactory::PreviewTileFactory()
{
    m_reader = new XMLReader("./../FinalMsp/Config/apppreviews.xml");
    m_factory = new WidgetFactory;
}

QList<TileItem*> PreviewTileFactory::previewTiles()
{
    QList<TileItem*> tiles;
    for(QDomElement e : *m_reader->allElemsUnderRoot())
    {
        TileItem* tile = new TileItem;
        tile->setText(e.tagName());
        tile->setWidget(m_factory->findWidget(e.tagName()));
        QDomElement color = m_reader->findElemUnderElem(e, "color");
        QList<QDomElement> values = *m_reader->allElemsUnderElem(color);
        tile->setColor(QColor(values[0].text().toInt(), values[1].text().toInt(), values[2].text().toInt(), values[3].text().toInt()));
        QDomElement textColor = m_reader->findElemUnderElem(e, "textcolor");
        values = *m_reader->allElemsUnderElem(textColor);
        tile->setTextColor(QColor(values[0].text().toInt(), values[1].text().toInt(), values[2].text().toInt(), values[3].text().toInt()));
        tiles.append(tile);
    }
    return tiles;
}

TileItem* PreviewTileFactory::tile(const QString& tagName)
{
    for(QDomElement e : *m_reader->allElemsUnderRoot())
    {
        if(e.tagName() == tagName)
        {
            TileItem* tile = new TileItem;
            tile->setText(e.tagName());
            tile->setWidget(m_factory->findWidget(e.tagName()));
            QDomElement color = m_reader->findElemUnderElem(e, "color");
            QList<QDomElement> values = *m_reader->allElemsUnderElem(color);
            tile->setColor(QColor(values[0].text().toInt(), values[1].text().toInt(), values[2].text().toInt(), values[3].text().toInt()));
            QDomElement textColor = m_reader->findElemUnderElem(e, "textcolor");
            values = *m_reader->allElemsUnderElem(textColor);
            tile->setTextColor(QColor(values[0].text().toInt(), values[1].text().toInt(), values[2].text().toInt(), values[3].text().toInt()));
            return tile;
        }
    }
    return nullptr;
}
