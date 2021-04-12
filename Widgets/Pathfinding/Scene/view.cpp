#include "view.h"

#include <QWheelEvent>

View::View(QWidget *parent) :
    QGraphicsView (parent)
{
    setDragMode(QGraphicsView::NoDrag);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scale(0.9, 0.9);
}

//EVENTS*************************************************
void View::scrollContentsBy(int i, int j)
{
    QGraphicsView::scrollContentsBy(i, j);
}

void View::resizeEvent(QResizeEvent* e)
{
    QGraphicsView::resizeEvent(e);
    centerOn(0, 0);
}
