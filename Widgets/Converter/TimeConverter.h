/**
 * @file TimeConverter.h
 *
 * @author Alexandra Voß
 *
 *
 */

#ifndef TIMECONVERTER_H
#define TIMECONVERTER_H

#include <cassert>

namespace timeconv
{

constexpr int MSECS_SECS_CONV_VAL = 1000;
constexpr int SECS_MIN_CONV_VAL = 60;
constexpr int MSECS_MIN_CONV_VAL = MSECS_SECS_CONV_VAL * SECS_MIN_CONV_VAL;
constexpr int SECS_HOUR_CONV_VAL = 3600;
constexpr int MSECS_HOUR_CONV_VAL = 3600000;

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
class TimeConverter
{
public:
    TimeConverter(T value)
    {
        assert(validType<T>::isValid);
        m_value = value;
    }
    void setValue(T value){
        assert(validType<T>::isValid);
        m_value = value;
    }
    T value() const {return m_value;}
    T msecsToSecs() const {return m_value / MSECS_SECS_CONV_VAL;}
    T msecsToMin() const {return m_value / MSECS_MIN_CONV_VAL;}
    T msecsToHour() const {return m_value / MSECS_HOUR_CONV_VAL;}
    T secsToMsecs() const {return m_value * MSECS_SECS_CONV_VAL;}
    T secsToMin() const {return m_value / SECS_MIN_CONV_VAL;}
    T secsToHour() const {return m_value / SECS_HOUR_CONV_VAL;}
    T minToMsecs() const {return m_value * MSECS_MIN_CONV_VAL;}
    T minToSecs() const {return m_value * SECS_MIN_CONV_VAL;}
    T minToHour() const {return m_value / SECS_MIN_CONV_VAL;}
    T hourToMsecs() const {return m_value * MSECS_HOUR_CONV_VAL;}
    T hourToSecs() const {return m_value * SECS_HOUR_CONV_VAL;}
    T hourToMin() const {return m_value * SECS_MIN_CONV_VAL;}

private:
    T m_value;
};

} //namespace

#endif // TIMECONVERTER_H

