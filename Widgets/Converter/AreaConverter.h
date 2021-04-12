/**
 * @file AreaConverter.h
 *
 * @author Alexandra Voß
 *
 *
 */
#ifndef AREACONVERTER_H
#define AREACONVERTER_H

#include <cassert>

namespace areaconv
{

constexpr int SQRCM_SQRM_CONV_VAL = 10000;
constexpr long long SQRCM_SQRKM_CONV_VAL = 10000000000;

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
class AreaConverter
{
public:
    AreaConverter(T value)
    {
        assert(validType<T>::isValid);
        m_value = value;
    }
    void setValue(T value){
        assert(validType<T>::isValid);
        m_value = value;
    }
    T value() const {return m_value;}
    T sqrCMToSQRM() const {return m_value / SQRCM_SQRM_CONV_VAL;}
    T sqrCMToSQRKM() const {return m_value / SQRCM_SQRKM_CONV_VAL;}
    T sqrMToSQRCM() const {return m_value * SQRCM_SQRM_CONV_VAL;}
    T sqrMToSQRKM() const {return m_value * SQRCM_SQRM_CONV_VAL;}
    T sqrKMToSQRCM() const {return m_value * SQRCM_SQRKM_CONV_VAL;}
    T sqrKMToSQRM() const {return m_value * SQRCM_SQRM_CONV_VAL;}

private:
    T m_value;
};

} //namespace

#endif // AREACONVERTER_H

