/**
 * @file MassConverter.h
 *
 * @author Alexandra Voß
 *
 *
 */

#ifndef MASSCONVERTER_H
#define MASSCONVERTER_H

#include <cassert>

namespace massconv
{

constexpr int MG_G_CONV_VAL = 1000;
constexpr int MG_KG_CONV_VAL = 1000000;

template <typename T> struct validType
{
    static const bool isValid = false;
};

template <> struct validType<int>
{
    static const bool isValid = true;
};

template <> struct validType<float>
{
    static const bool isValid = true;
};

template <> struct validType<double>
{
    static const bool isValid = true;
};

template<typename T>
class MassConverter
{
public:
    MassConverter(T value)
    {
        assert(validType<T>::isValid);
        m_value = value;
    }
    void setValue(T value){
        assert(validType<T>::isValid);
        m_value = value;
    }
    T value() const {return m_value;}
    T mgToG() const {return m_value / MG_G_CONV_VAL;}
    T mgToKG() const {return m_value / MG_KG_CONV_VAL;}
    T gToMG() const {return m_value * MG_G_CONV_VAL;}
    T gToKG() const {return m_value * MG_G_CONV_VAL;}
    T kgToMG() const {return m_value * MG_KG_CONV_VAL;}
    T kgToG() const {return m_value * MG_G_CONV_VAL;}

private:
    T m_value;
};

} //namespace

#endif // MASSCONVERTER_H
