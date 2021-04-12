#ifndef UTILS_H
#define UTILS_H

#include "constants.h"
#include "Utils/vector2d.h"
#include "QPointF"

using Vec = Vector2d<double>;

template <typename T>
T sqr(const T &v) {return v * v;}

inline double radian(double d){return d * (PI/180);};

inline int sgn(int x){
    int v;
    (x < 0) ? v = -1 : v = 1;
    return v;
}

inline QPointF v2p(const Vec& vec){return QPointF(vec.x(), vec.y());}

inline Vec p2v(const QPointF& p){return Vec(p.x(), p.y());}

#endif // UTILS_H
