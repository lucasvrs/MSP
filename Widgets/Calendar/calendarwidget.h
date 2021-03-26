#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>

class CalendarMonthGroupBox;
class DayDetailsBgWidget;
class QDate;
class QGridLayout;
class QLabel;
class SearchDialog;

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
    CalendarWidget(QWidget* parent = nullptr);

private:
    bool m_detailsOpen;
    bool m_validateOpen;
    CalendarMonthGroupBox* m_monthGroupBox;
    DayDetailsBgWidget* m_bg;
    QDate* m_curDate;
    QGridLayout* m_layout;
    QLabel* m_headerLabel;
    SearchDialog* m_dialog = nullptr;
    void deleteMonthGroupBox();

protected:
    void mouseReleaseEvent(QMouseEvent* e) override;
    void resizeEvent(QResizeEvent* e) override;

public slots:
    void openDetails(const QDate& date);
    void showNextMonth();
    void showPrevMonth();
};

#endif // CALENDARWIDGET_H
