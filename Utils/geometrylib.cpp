#include "geometrylib.h"

double angleVectorVector(const Vec &first, const Vec &second)
{
    double scalar = first * second;
    return acos(scalar/(first.length() * second.length())) * (180/PI);
}

const Vec &nearestPoint(const Vec& point, const Vec& cPoint1, const Vec& cPoint2)
{
    if((cPoint1 - point).length() > (cPoint2 - point).length()){ return cPoint2; }
    return cPoint1;
}

bool hasLineLineIntersection(const LineSegment& seg, const LineSegment &seg2, Vec& ip)
{
    double x1 = seg2.p0.x();
    double x2 = seg2.p1.x();
    double y1 = seg2.p0.y();
    double y2 = seg2.p1.y();
    double x3 = seg.p0.x();
    double x4 = seg.p1.x();
    double y3 = seg.p0.y();
    double y4 = seg.p1.y();
    double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if(den == 0) return false;

    double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4))/den;
    double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3))/den;

    if(0 <= t && t <= 1 && 0 <= u)
    {
        double x = x1 + t * (x2 - x1);
        double y = y1 + t * (y2 - y1);
        ip = Vec(x, y);
        return true;
    }
    return false;
}

bool hasLineCircleIntersection(const LineSegment& seg, const Circle& c, Vec& ip)
{
    Vec d = seg.dir();
    double disSegment = d.lengthSqrd();
    //double D = (seg.p0 - c.p ^ seg.p1 - c.p).z();
    Vec xVec = (seg.p0 - c.p);
    Vec yVec = (seg.p1 - c.p);
    double D = xVec.x() * yVec.y() - xVec.y() * yVec.x();
    double delta = sqr(c.r) * disSegment - sqr(D);

    if(delta < 0.0){ return false; }

    delta = sqrt(delta);
    Vec dd(D * d);

    if(delta < 0.001){ return false; }

    double tx = (d.y() < 0.0 ? -1.0 : 1.0) * d.x() * delta;
    double ty = fabs(d.y()) * delta;

    Vec pseudo1(dd.y() + tx, -dd.x() + ty);
    Vec pseudo2(dd.y() - tx, -dd.x() - ty);
    Vec ip1 = c.p + pseudo1 / disSegment;
    Vec ip2 = c.p + pseudo2 / disSegment;
    ip = nearestPoint(seg.p0, ip1, ip2);
    double t = d * (ip1 - seg.p0) / disSegment;
    if(t < 0) return false;
    //t[1] = d * (ip[1] - ls.p0) / disSegment;

    return true;
}
