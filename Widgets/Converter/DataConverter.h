/**
 * @file DataConverter.h
 *
 * @author Alexandra Voß
 *
 *
 */

#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include <cassert>

namespace dataconv
{

constexpr int KB_MB_CONV_VAL = 1000;
constexpr int KB_GB_CONV_VAL = 1000000;
constexpr int KB_TB_CONV_VAL = 1000000000;

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
class DataConverter
{
public:
    DataConverter(T value)
    {
        assert(validType<T>::isValid);
        m_value = value;
    }
    void setValue(T value){
        assert(validType<T>::isValid);
        m_value = value;
    }
    T value() const {return m_value;}
    T kbToMB() const {return m_value / KB_MB_CONV_VAL;}
    T kbToGB() const {return m_value / KB_GB_CONV_VAL;}
    T kbToTB() const {return m_value / KB_TB_CONV_VAL;}
    T mbToKB() const {return m_value * KB_MB_CONV_VAL;}
    T mbToGB() const {return m_value / KB_MB_CONV_VAL;}
    T mbToTB() const {return m_value / KB_GB_CONV_VAL;}
    T gbToKB() const {return m_value * KB_GB_CONV_VAL;}
    T gbToMB() const {return m_value * KB_MB_CONV_VAL;}
    T gbToTB() const {return m_value / KB_MB_CONV_VAL;}
    T tbToKB() const {return m_value * KB_TB_CONV_VAL;}
    T tbToMB() const {return m_value * KB_GB_CONV_VAL;}
    T tbToGB() const {return m_value * KB_MB_CONV_VAL;}

private:
    T m_value;
};

} //namespace

#endif // DATACONVERTER_H

