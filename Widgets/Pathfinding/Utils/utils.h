#ifndef UTILS_H
#define UTILS_H

#include <QPointF>

extern double distance(const QPointF& first, const QPointF& second)
{
    double x = (second.x() - first.x());
    double y = (second.y() - first.y());
    return sqrt(x * x + y * y);
}

#endif // UTILS_H
