#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include <QList>

class XMLReader;
class XMLWriter;
class TileItem;
class WidgetFactory;
class PreviewTileFactory;

class TileFactory
{
public:
    TileFactory();
    QList<TileItem*> tiles();
    void createTile(const QString& name, const QColor& color, const QColor &textColor);
    void deleteTile(const QString& name, int id);

private:
    XMLReader* m_reader;
    XMLWriter* m_writer;
    WidgetFactory* m_factory;
    PreviewTileFactory* m_previewFactory;
};

#endif // TILEFACTORY_H
