/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "calendarmonthgroupbox.h"
#include "daygroupbox.h"
#include <QDate>
#include <QGridLayout>
#include <QDebug>
#include "Xml/xmlreader.h"
#include <QDomElement>

CalendarMonthGroupBox::CalendarMonthGroupBox(const QDate &date, QWidget *parent) :
    QGroupBox(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //define layout
    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    //defines month layout
    int dayInCurMonth, weekday, dayInNextMonth, prevMonth, prevYear, nextMonth, nextYear, month, year, daysInCurMonth, firstDayInWeek, row;
    month = date.month();
    year = date.year();
    dayInCurMonth = weekday = dayInNextMonth = 1;
    row = 0;
    prevMonth = nextMonth = month;
    prevYear = nextYear = year;
    QDate curMonth(year, month, 1);
    daysInCurMonth = curMonth.daysInMonth();
    firstDayInWeek = curMonth.dayOfWeek();
    if(month == 1)
    {
        prevMonth = 12;
        prevYear--;
        nextMonth++;
    }
    if(month == 12)
    {
        prevMonth--;
        nextMonth = 1;
        nextYear++;
    }
    else
    {
        prevMonth--;
        nextMonth++;
    }
    QDate lastMonth(prevYear, prevMonth, 1);
    int firstRowLimit = lastMonth.daysInMonth();
    QDate next(nextYear, nextMonth, 1);
    while(row < 6)
    {
        while(weekday < 8)
        {
            if(row == 0 && weekday < firstDayInWeek)
            {
                lastMonth.setDate(prevYear, prevMonth, firstRowLimit - ((firstDayInWeek - 1) - weekday));
                addDay(lastMonth, row, weekday, false);
            }
            else
            {
                if(dayInCurMonth <= daysInCurMonth)
                {
                    curMonth.setDate(year, month, dayInCurMonth);
                    addDay(curMonth, row, weekday);
                    dayInCurMonth++;
                }
                else
                {
                    next.setDate(nextYear, nextMonth, dayInNextMonth);
                    addDay(next, row, weekday, false);
                    dayInNextMonth++;
                }
            }
            weekday++;
        }
        weekday = 1;
        row++;
    }
}

/*! Returns DayGroupBox fitting passed date
 * \brief CalendarMonthGroupBox::getDayBox
 * \param date - QDate of DayGroupBox
 * \return DayGroupBox
 */
DayGroupBox* CalendarMonthGroupBox::getDayBox(const QDate &date)
{
    for(DayGroupBox* day : m_dayBoxes)
    {
        if(day->date() == date)
        {
            return day;
        }
    }
    return nullptr;
}

/*! Adds DayGroupBox fitting passed date to layout
 * \brief CalendarMonthGroupBox::addDay
 * \param date          - QDate of DayGroupBox
 * \param row           - Row in layout
 * \param weekday       - Column in layout
 * \param isCurMonth    - Wether day is located in the current month
 */
void CalendarMonthGroupBox::addDay(const QDate& date, int row, int weekday, bool isCurMonth)
{
    DayGroupBox* day = new DayGroupBox(date, isCurMonth);
    (isCurMonth) ? day->setObjectName("curMonth") : day->setObjectName("otherMonth");
    connect(day, &DayGroupBox::clicked, this, &CalendarMonthGroupBox::dayClicked);
    m_layout->addWidget(day, row, weekday - 1);
    m_dayBoxes.append(day);
}
