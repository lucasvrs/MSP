#include "previewtilesview.h"
#include "previewtilescene.h"

PreviewTilesView::PreviewTilesView(QWidget *parent) : QGraphicsView(parent)
{
    m_scene = new PreviewTileScene;
    setScene(m_scene);
    setDragMode(QGraphicsView::NoDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    //connects
    connect(m_scene, &PreviewTileScene::showWidget, this, &PreviewTilesView::showWidget);
}

//EVENTS********************************************************
void PreviewTilesView::resizeEvent(QResizeEvent* e)
{
    QGraphicsView::resizeEvent(e);
    m_scene->updateScene(width());
    centerOn(0, 0);
}

void PreviewTilesView::scrollContentsBy(int, int v)
{
    QGraphicsView::scrollContentsBy(0, v);
}
