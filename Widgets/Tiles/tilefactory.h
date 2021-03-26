#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include <QList>

class XMLReader;
class TileItem;
class WidgetFactory;

class TileFactory
{
public:
    TileFactory();
    QList<TileItem*> tiles();

private:
    XMLReader* m_reader;
    WidgetFactory* m_factory;
};

#endif // TILEFACTORY_H
