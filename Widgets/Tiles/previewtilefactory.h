#ifndef PREVIEWTILEFACTORY_H
#define PREVIEWTILEFACTORY_H

#include <QList>

class XMLReader;
class TileItem;
class WidgetFactory;

class PreviewTileFactory
{
public:
    PreviewTileFactory();
    QList<TileItem*> previewTiles();
    TileItem* tile(const QString& tagName);

private:
    XMLReader* m_reader;
    WidgetFactory* m_factory;
};

#endif // PREVIEWTILEFACTORY_H
