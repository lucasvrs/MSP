#ifndef TILESVIEW_H
#define TILESVIEW_H

#include <QGraphicsView>
#include "tileitem.h"

class TileScene;
//class TileItem;

class TilesView : public QGraphicsView
{
    Q_OBJECT
public:
    TilesView(QWidget* parent = nullptr);

private:
    TileScene* m_scene;

protected:
    void resizeEvent(QResizeEvent* e) override;
    void scrollContentsBy(int, int v) override;

signals:
    void showSubject(const QString& title, QList<TileItem*> list);
};

#endif // TILESVIEW_H
