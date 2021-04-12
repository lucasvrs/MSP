#include "handleitem.h"
#include "Widgets/ColorPicker/Widgets/Spectrum/Utils/colorspectrum.h"
#include <QPainter>

HandleItem::HandleItem(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void HandleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QRadialGradient q(0, 0, 10, 0, 0);
    q.setColorAt(0, Qt::white);
    QBrush b(q);
    painter->setBrush(b);
    painter->drawEllipse(boundingRect());
}

QRectF HandleItem::boundingRect() const
{
    return {-10, -10, 20, 20};
}

QColor HandleItem::getColor(int w)
{
    const double f1 = 1.0 / 400;
    const double f2 = 1.0 / 780;
    double freq = ColorSpectrum::linMap(0, x(), w, f1, f2);
    return ColorSpectrum::waveLengthToColor(1.0 / freq);
}
