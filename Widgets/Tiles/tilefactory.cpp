#include "tilefactory.h"
#include "Xml/xmlreader.h"
#include "tileitem.h"
#include <QDomDocument>

TileFactory::TileFactory()
{
    m_reader = new XMLReader("./../FinalMsp/Config/tileconfig.xml");
}

QList<TileItem*> TileFactory::tiles()
{
    QList<TileItem*> tiles;
    for(QDomElement e : *m_reader->allElemsUnderRoot())
    {
        TileItem* tile = new TileItem;
        tile->setText(e.tagName());
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
