#ifndef ADDPREVIEWSCENE_H
#define ADDPREVIEWSCENE_H

#include <QGraphicsScene>
#include <QList>

class PreviewTileFactory;
class TileItem;

class AddPreviewScene : public QGraphicsScene
{
    Q_OBJECT

public:
    AddPreviewScene(QObject* parent = nullptr);

private:
    double m_width;
    double m_height;
    double m_tileLength;
    PreviewTileFactory* m_factory;
    QList<TileItem*> m_tiles;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e) override;

signals:
    void addTile(TileItem* tile);

private slots:
    void addItems();
    void deleteItems();

public slots:
    void updateScene(double w);
};

#endif // ADDPREVIEWSCENE_H
