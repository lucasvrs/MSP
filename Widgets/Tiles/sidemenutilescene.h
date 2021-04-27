#ifndef SIDEMENUTILESCENE_H
#define SIDEMENUTILESCENE_H

#include <QGraphicsScene>

class TileItem;
class AddPreviewDialog;

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
    AddPreviewDialog* m_dialog;
    QString m_title;
    int m_id;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* e);

signals:
    void addTile();
    void showWidget(QWidget* w);

private slots:
    void deleteItems();
    void editTile(TileItem* tile);
    void removeTile(TileItem *tile);

public slots:
    void addItems(QList<TileItem*> tiles);
    void updateScene(double w);
    void setPreview(QList<TileItem*> previews);
    void setTitle(const QString& title);
    void setId(int id);
};

#endif // SIDEMENUTILESCENE_H
