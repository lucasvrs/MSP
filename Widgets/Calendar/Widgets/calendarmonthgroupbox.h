#ifndef CALENDARMONTHGROUPBOX_H
#define CALENDARMONTHGROUPBOX_H

#include <QGroupBox>

class QGridLayout;
class DayGroupBox;

class CalendarMonthGroupBox : public QGroupBox
{
    Q_OBJECT

public:
    CalendarMonthGroupBox(const QDate& date, QWidget* parent = nullptr);
    void addDay(const QDate& date, int row, int weekday, bool isCurMonth = true);
    DayGroupBox* getDayBox(const QDate& date);

private:
    QGridLayout* m_layout;
    QList<DayGroupBox*> m_dayBoxes;

signals:
    void dayClicked(const QDate& date);
};

#endif // CALENDARMONTHGROUPBOX_H
