/**
 * @file LengthConverter.h
 *
 * @author Alexandra Voß
 *
 *
 */
#ifndef LENGTHCONVERTER_H
#define LENGTHCONVERTER_H

#include <cassert>

namespace lengthconv
{

constexpr short MM_CM_CONV_VAL = 10;
constexpr short CM_M_CON_VAL = 100;
constexpr int M_KM_CON_VAL = 1000;
constexpr int MM_M_CONV_VAL = MM_CM_CONV_VAL * CM_M_CON_VAL;
constexpr int MM_KM_CONV_VAL = MM_M_CONV_VAL * M_KM_CON_VAL;
constexpr int CM_KM_CONV_Val = CM_M_CON_VAL * M_KM_CON_VAL;

enum UnitOfLength
{
    MILLIMETER = 0,
    CENTIMETER,
    METER,
    KILOMETER
};

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
class LengthConverter
{
public:
    LengthConverter(T value)
    {
        assert(validType<T>::isValid);
        m_value = value;
    }
    void setValue(T value){
        assert(validType<T>::isValid);
        m_value = value;
    }
    T value() const {return m_value;}
    T mmToCm() const {return m_value / MM_CM_CONV_VAL;}
    T mmToM() const {return m_value / MM_M_CONV_VAL;}
    T mmToKM() const {return m_value / MM_KM_CONV_VAL;}
    T cmToMM() const {return m_value * MM_CM_CONV_VAL;}
    T cmToM() const {return m_value / CM_M_CON_VAL;}
    T cmToKM() const {return m_value / CM_KM_CONV_Val;}
    T mToMM() const {return m_value * MM_M_CONV_VAL;}
    T mToCM() const {return m_value * CM_M_CON_VAL;}
    T mToKM() const {return m_value / M_KM_CON_VAL;}
    T kmToMM() const {return m_value * MM_KM_CONV_VAL;}
    T kmToCM() const {return m_value * CM_KM_CONV_Val;}
    T kmToM() const {return m_value * M_KM_CON_VAL;}
    T convert(UnitOfLength from, UnitOfLength to) const
    {
        return m_matrix[from][to];
    }

private:
    T m_value;

    using TLC = LengthConverter<T>;
    using MPtr = T (TLC::*)() const;
    const MPtr m_matrix[4][4] = {
        {&TLC::value, &TLC::mmToCm, &TLC::mmToM, &TLC::mmToKM},
        {&TLC::cmToMM, &TLC::value, &TLC::cmToM, &TLC::cmToKM},
        {&TLC::mToMM, &TLC::mToCM, &TLC::value, &TLC::mToKM},
        {&TLC::kmToMM, &TLC::kmToCM, &TLC::kmToM, &TLC::value}
    };
};

} //namespace

#endif // LENGTHCONVERTER_H
