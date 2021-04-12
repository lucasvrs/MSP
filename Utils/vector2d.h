#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
#include <QDebug>
#include "utils.h"

template<typename T>
class Vector2d
{
public:
    //Constructors
    Vector2d() : m_v{0, 0}{}
    Vector2d(T x, T y) : m_v{x, y}{}
    //methods
    void invert(){m_v = {-m_v[0], -m_v[1]};}
    Vector2d inverted() const{return {-m_v[0], -m_v[1]};}
    T length() const{return std::sqrt(lengthSqrd());}
    T lengthSqrd() const{return sqr(m_v[0]) + sqr(m_v[1]);}
    void normalize()
    {
        T l = length();
        *this = *this/l;
    }
    Vector2d normalized() const
    {
        Vector2d vec(*this);
        vec.normalize();
        return vec;
    }
    Vector2d perpendicular() const{return {-m_v[1], m_v[0]};}
    void rotate(double a)
    {
        const double rad = radian(a);
        const double x = m_v[0];
        const double y = m_v[1];
        m_v[0] = x * std::cos(rad) - y * std::sin(rad);
        m_v[1] = x * std::sin(rad) + y * std::cos(rad);
    }
    Vector2d rotated(double a)
    {
        Vector2d vec(*this);
        vec.rotate(a);
        return vec;
    }
    //getter
    T x() const{return m_v[0];}
    T y() const{return m_v[1];}
    //setter
    T& x(){return m_v[0];}
    T& y(){return m_v[1];}
    //operators
    const T &operator[](int i) const{return m_v[i];}
    T& operator[](int i){return m_v[i];}
    T operator*(const Vector2d& vec) const
    {
        return m_v[0] * vec.x() + m_v[1] * vec.y();
    }
    Vector2d operator*(T s) const
    {
        return Vector2d(m_v[0] * s, m_v[1] * s);
    }
    friend Vector2d operator*(T s, const Vector2d& me)
    {
        return me * s;
    }
    Vector2d operator/(T d) const
    {
        return {m_v[0]/d, m_v[1]/d};
    }
    Vector2d operator+(const Vector2d& vec) const
    {
        return Vector2d(m_v[0] + vec.x(), m_v[1] + vec.y());
    }
    friend Vector2d operator+(T v, const Vector2d& me)
    {
        return me + v;
    }
    Vector2d operator-(const Vector2d& vec) const
    {
        return Vector2d(m_v[0] - vec.x(), m_v[1] - vec.y());
    }
    bool operator==(const Vector2d& vec) const
    {
        return (m_v[0] == vec.x() && m_v[1] == vec.y());
    }
    bool operator!=(const Vector2d& vec) const
    {
        return !(m_v[0] == vec.x() && m_v[1] == vec.y());
    }
    bool operator<(const Vector2d& vec) const
    {
        if(m_v[0] == vec.x())
        {
            return (m_v[1] < vec.y());
        }
        return (m_v[0] < vec.x());
    }
    bool operator>(const Vector2d& vec) const
    {
        return !(*this < vec);
    }

private:
    T m_v[2];
};

template <typename T>
QDebug &operator<<(QDebug dbg, const Vector2d<T> &v)
{
    return dbg << "{" << v[0] << v[1] << "}";
}

#endif // VECTOR2D_H
