#ifndef TILESCENE_H
#define TILESCENE_H

#include <QGraphicsScene>

class TileFactory;
class TileItem;
class CreateCollectionDialog;

class TileScene : public QGraphicsScene
{
    Q_OBJECT
public:
    TileScene(QObject* parent = nullptr);

private:
    const short m_cols = 5;
    double m_width;
    double m_height;
    double m_tileLength;
    TileFactory* m_factory;
    QList<TileItem*> m_tiles;
    CreateCollectionDialog* m_dialog;
    int m_lastId;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* e) override;

signals:
    void showSubject(const QString& title, QList<TileItem*> list, int id);

private slots:
    void addItems();
    void deleteItems();
    void removeTile(TileItem *tile);

public slots:
    void updateScene(double w);
    void openLastSubject();
};

#endif // TILESCENE_H
