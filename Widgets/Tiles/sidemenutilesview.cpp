/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "sidemenutilesview.h"
#include "sidemenutilescene.h"
#include "tileitem.h"
#include <QDebug>

SideMenuTilesView::SideMenuTilesView(QWidget *parent) : QGraphicsView(parent)
{
    m_scene = new SideMenuTileScene;
    setScene(m_scene);
    setDragMode(QGraphicsView::NoDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    setFixedWidth(200);

    //connects
    connect(m_scene, &SideMenuTileScene::showWidget, this, &SideMenuTilesView::showWidget);
    connect(m_scene, &SideMenuTileScene::addTile, this, &SideMenuTilesView::addTile);
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

void SideMenuTilesView::setTitle(const QString& title)
{
    m_scene->setTitle(title);
}

void SideMenuTilesView::setId(int id)
{
    m_scene->setId(id);
}
