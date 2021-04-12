#include "spectrumsview.h"

SpectrumsView::SpectrumsView(QWidget *parent) :
    QGraphicsView (parent)
{
    setDragMode(QGraphicsView::NoDrag);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void SpectrumsView::scrollContentsBy(int, int)
{
    QGraphicsView::scrollContentsBy(0, 0);
}
