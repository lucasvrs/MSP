#ifndef TILESCENE_H
#define TILESCENE_H

#include <QGraphicsScene>

class TileFactory;
class TileItem;

class TileScene : public QGraphicsScene
{
    Q_OBJECT
public:
    TileScene(QObject* parent = nullptr);

private:
    double m_width;
    double m_height;
    double m_tileLength;
    TileFactory* m_factory;
    QList<TileItem*> m_tiles;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e) override;

signals:
    void showSubject(const QString& title);

private slots:
    void addItems();
    void deleteItems();

public slots:
    void updateScene(double w);
};

#endif // TILESCENE_H
