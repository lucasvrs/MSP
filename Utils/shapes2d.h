#ifndef SHAPES2D_H
#define SHAPES2D_H

#include "Widgets/Raytracing/Utils/utils.h"

struct Shape
{
    enum ShapeType
    {
        LineSegment = 0,
        Circle
    };
    virtual ShapeType type() = 0;
};

struct LineSegment : public Shape
{
    Vec p0;
    Vec p1;
    LineSegment() : p0(Vec()), p1(Vec()){}
    LineSegment(Vec s, Vec d) : p0(s), p1(d){}
    ShapeType type(){return ShapeType::LineSegment;}
    double length() const{return std::abs((p1 - p0).length());}
    Vec dir() const{return p1 - p0;}

};

struct Circle : public Shape
{
    Vec p;
    double r;
    Circle() : p(Vec()), r(10){}
    Circle(Vec c, double rad) : p(c), r(rad){}
    ShapeType type(){return ShapeType::Circle;}
    double diameter() const{return 2 * r;}
};

#endif // SHAPES2D_H
