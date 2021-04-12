#include "addpreviewview.h"
#include "tileitem.h"
#include "addpreviewscene.h"

AddPreviewView::AddPreviewView(QWidget *parent) : QGraphicsView(parent)
{
    m_scene = new AddPreviewScene;
    setScene(m_scene);
    setDragMode(QGraphicsView::NoDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    //connects
    connect(m_scene, &AddPreviewScene::addTile, this, &AddPreviewView::addTile);
}

//EVENTS********************************************************
void AddPreviewView::resizeEvent(QResizeEvent* e)
{
    QGraphicsView::resizeEvent(e);
    m_scene->updateScene(width());
    centerOn(0, 0);
}

void AddPreviewView::scrollContentsBy(int, int v)
{
    QGraphicsView::scrollContentsBy(0, v);
}
