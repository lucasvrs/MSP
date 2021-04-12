/**
 * @file VolumeConverter.h
 *
 * @author Alexandra Voß
 *
 *
 */

#ifndef VOLUMECONVERTER_H
#define VOLUMECONVERTER_H

#include <cassert>

namespace volumeconv
{

constexpr int ML_CL_CONV_VAL = 10;
constexpr int ML_DL_CONV_VAL = 100;
constexpr int ML_L_CONV_VAL = 1000;

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
class VolumeConverter
{
public:
    VolumeConverter(T value)
    {
        assert(validType<T>::isValid);
        m_value = value;
    }
    void setValue(T value){
        assert(validType<T>::isValid);
        m_value = value;
    }
    T value() const {return m_value;}
    T mlToCL() const {return m_value / ML_CL_CONV_VAL;}
    T mlToDL() const {return m_value / ML_DL_CONV_VAL;}
    T mlToL() const {return m_value / ML_L_CONV_VAL;}
    T clToML() const {return m_value * ML_CL_CONV_VAL;}
    T clToDL() const {return m_value / ML_CL_CONV_VAL;}
    T clToL() const {return m_value / ML_DL_CONV_VAL;}
    T dlToML() const {return m_value * ML_DL_CONV_VAL;}
    T dlToCL() const {return m_value * ML_CL_CONV_VAL;}
    T dlToL() const {return m_value / ML_CL_CONV_VAL;}
    T lToML() const {return m_value * ML_L_CONV_VAL;}
    T lToCL() const {return m_value * ML_DL_CONV_VAL;}
    T lToDL() const {return m_value * ML_CL_CONV_VAL;}

private:
    T m_value;
};

} //namespace

#endif // VOLUMECONVERTER_H

