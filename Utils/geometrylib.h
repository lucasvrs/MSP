#ifndef GEOMETRYLIB_H
#define GEOMETRYLIB_H

#include "shapes2d.h"

extern double angleVectorVector(const Vec &first, const Vec &second);
extern const Vec& nearestPoint(const Vec& point, const Vec& cPoint1, const Vec& cPoint2);
extern bool hasLineLineIntersection(const LineSegment& seg, const LineSegment& seg2, Vec& ip);
extern bool hasLineCircleIntersection(const LineSegment& seg, const Circle& c, Vec& ip);

#endif // GEOMETRYLIB_H
