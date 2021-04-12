/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "sidemenutilesview.h"
#include "sidemenutilescene.h"
#include <QDebug>

SideMenuTilesView::SideMenuTilesView(QWidget *parent) : QGraphicsView(parent)
{
    m_scene = new SideMenuTileScene;
    setScene(m_scene);
    setDragMode(QGraphicsView::NoDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    setFixedWidth(100);

    //connects
    connect(m_scene, &SideMenuTileScene::showWidget, this, &SideMenuTilesView::showWidget);
}

//EVENTS********************************************************
void SideMenuTilesView::resizeEvent(QResizeEvent* e)
{
    QGraphicsView::resizeEvent(e);
    m_scene->updateScene(width());
    centerOn(0, 0);
}

void SideMenuTilesView::scrollContentsBy(int, int v)
{
    QGraphicsView::scrollContentsBy(0, v);
}

//SLOTS********************************************************
void SideMenuTilesView::setPreview(QList<TileItem*> previews)
{
    m_scene->setPreview(previews);
}
