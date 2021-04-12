#include "Widgets/LiteratureEras/eraview.h"
#include <QWheelEvent>

EraView::EraView(QWidget *parent) :
    QGraphicsView (parent)
{
    setDragMode(QGraphicsView::ScrollHandDrag);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void EraView::scrollContentsBy(int value, int)
{
    QGraphicsView::scrollContentsBy(value, 0);
}

void EraView::wheelEvent(QWheelEvent* e)
{
    if(e->modifiers() == Qt::ALT)
    {
        QGraphicsView::wheelEvent(e);
    }
}
