#ifndef PREVIEWTILESCENE_H
#define PREVIEWTILESCENE_H

#include <QGraphicsScene>
#include <QList>

class PreviewTileFactory;
class TileItem;

class PreviewTileScene : public QGraphicsScene
{
    Q_OBJECT

public:
    PreviewTileScene(QObject* parent = nullptr);

private:
    double m_width;
    double m_height;
    double m_tileLength;
    PreviewTileFactory* m_factory;
    QList<TileItem*> m_tiles;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e) override;

signals:
    void showWidget(QWidget* widget);

private slots:
    void addItems();
    void deleteItems();

public slots:
    void updateScene(double w);
};

#endif // PREVIEWTILESCENE_H
