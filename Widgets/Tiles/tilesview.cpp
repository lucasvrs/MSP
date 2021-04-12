/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "tilesview.h"
#include "tilescene.h"

TilesView::TilesView(QWidget *parent) : QGraphicsView(parent)
{
    m_scene = new TileScene;
    setScene(m_scene);
    setDragMode(QGraphicsView::NoDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    //connects
    connect(m_scene, &TileScene::showSubject, this, &TilesView::showSubject);
}

//EVENTS********************************************************
void TilesView::resizeEvent(QResizeEvent* e)
{
    QGraphicsView::resizeEvent(e);
    m_scene->updateScene(width());
    centerOn(0, 0);
}

void TilesView::scrollContentsBy(int, int v)
{
    QGraphicsView::scrollContentsBy(0, v);
}
