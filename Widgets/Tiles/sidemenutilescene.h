#ifndef SIDEMENUTILESCENE_H
#define SIDEMENUTILESCENE_H

#include <QGraphicsScene>

class TileItem;

class SideMenuTileScene : public QGraphicsScene
{
    Q_OBJECT
public:
    SideMenuTileScene(QObject* parent = nullptr);

private:
    bool m_alreadyAdded;
    double m_width;
    double m_height;
    double m_tileLength;
    QList<TileItem*> m_tiles;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);

signals:
    void showWidget(QWidget* w);

private slots:
    void deleteItems();

public slots:
    void addItems(QList<TileItem*> tiles);
    void updateScene(double w);
    void setPreview(QList<TileItem*> previews);
};

#endif // SIDEMENUTILESCENE_H
