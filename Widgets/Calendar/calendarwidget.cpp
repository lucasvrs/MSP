/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "Utils/calendarconstants.h"
#include "Widgets/calendarmonthgroupbox.h"
#include "calendarwidget.h"
#include "Widgets/daydetailsbgwidget.h"
#include "Widgets/searchdialog.h"
#include "Widgets/daygroupbox.h"
#include <QDateTime>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>

CalendarWidget::CalendarWidget(QWidget *parent) :
    QWidget(parent),
    m_detailsOpen(false),
    m_validateOpen(false),
    m_bg(new DayDetailsBgWidget(QDate()))
{
    setAutoFillBackground(true);
    m_layout = new QGridLayout(this);

    m_curDate = new QDate(QDateTime::currentDateTime().date());

    //define fonts
    QFont headerFont("Agency FB", 17);
    headerFont.setBold(true);
    QFont font("Agency FB", 15);
    QFont arrowFont("Helvetica", 25, 15);
    QFontMetrics m(arrowFont);

    //style header label
    m_headerLabel = new QLabel((*m_curDate).toString("MMMM yyyy"));
    m_headerLabel->setFont(headerFont);
    m_headerLabel->setAlignment(Qt::AlignCenter);
    m_headerLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_layout->addWidget(m_headerLabel, 0, 1, 1, 7);

    //adds search button
    QPushButton* searchBtn = new QPushButton("");
    m_layout->addWidget(searchBtn, 0, 8);

    //adds weekday labels
    for(int i = 0; i < 7; i++)
    {
        QLabel* weekdayLabel = new QLabel(WEEKDAY[i]);
        weekdayLabel->setFont(font);
        weekdayLabel->setAlignment(Qt::AlignCenter);
        weekdayLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        m_layout->addWidget(weekdayLabel, 1, 1 + i, 1, 1);
    }

    //defines, styles and adds navigation buttons
    QPushButton* prevMonthBtn = new QPushButton("<");
    QPushButton* nextMonthBtn = new QPushButton(">");
    QPushButton* navBtns[2] = {prevMonthBtn, nextMonthBtn};
    for(QPushButton* btn : navBtns)
    {
        btn->setObjectName("navBtns");
        btn->setFixedWidth(m.width(btn->text()) + 5);
        btn->setFont(arrowFont);
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    }
    m_layout->addWidget(prevMonthBtn, 2, 0, 1, 1);
    m_layout->addWidget(nextMonthBtn, 2, 8, 1, 1);

    //adds month groupbox
    m_monthGroupBox = new CalendarMonthGroupBox(*m_curDate);
    m_layout->addWidget(m_monthGroupBox, 2, 1, 1, 7);

    //adds connects
    connect(prevMonthBtn, &QPushButton::clicked, this, &CalendarWidget::showPrevMonth);
    connect(nextMonthBtn, &QPushButton::clicked, this, &CalendarWidget::showNextMonth);
    connect(m_monthGroupBox, &CalendarMonthGroupBox::dayClicked, this, &CalendarWidget::openDetails);
    connect(searchBtn, &QPushButton::clicked, [this]()
    {
        //adds searchdialog
        if(m_dialog == nullptr)
        {
            m_dialog = new SearchDialog(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
            m_dialog->show();
            connect(m_dialog, &SearchDialog::dateChanged, [this](const QDate& date)
            {
                m_curDate = new QDate(date);
                deleteMonthGroupBox();
            });
            connect(m_dialog, &SearchDialog::closed, [this]()
            {
                m_dialog = nullptr;
            });
        }
        else
        {
            m_dialog->raise();
        }
    });

    //adds icon to search button
    QPixmap map("./../Kalender/unnamed");
    searchBtn->setIcon(QIcon(map));
}

/*! Deletes the current month groupbox and opens a new one with the new date
 * \brief CalendarWidget::deleteMonthGroupBox
 */
void CalendarWidget::deleteMonthGroupBox()
{
    QLayoutItem* item = m_layout->takeAt(m_layout->indexOf(m_monthGroupBox));
    delete item->widget();
    delete item;
    m_monthGroupBox = new CalendarMonthGroupBox(*m_curDate);
    connect(m_monthGroupBox, &CalendarMonthGroupBox::dayClicked, this, &CalendarWidget::openDetails);
    m_layout->addWidget(m_monthGroupBox, 2, 1, 1, 7);
    m_headerLabel->setText((*m_curDate).toString("MMMM yyyy"));
}

//EVENTS**************************************************************************
void CalendarWidget::mouseReleaseEvent(QMouseEvent* e)
{
    QWidget::mouseReleaseEvent(e);
}

void CalendarWidget::resizeEvent(QResizeEvent* e)
{
    QWidget::resizeEvent(e);
    if(m_bg != nullptr) m_bg->setGeometry(geometry());
}

//SLOTS***************************************************************************
/*! Opens the details of the selected day
 * \brief CalendarWidget::openDetails
 * \param date
 */
void CalendarWidget::openDetails(const QDate& date)
{
    m_bg = new DayDetailsBgWidget(date, this);
    m_bg->setGeometry(geometry());
    m_bg->show();
    connect(m_bg, &DayDetailsBgWidget::clicked, [this]()
    {
        m_bg->deleteLater();
        m_bg = nullptr;
    });
    connect(m_bg, &DayDetailsBgWidget::needsUpdate, [this](const QDate& date)
    {
        DayGroupBox* day = m_monthGroupBox->getDayBox(date);
        if(day != nullptr) day->addAppointments();
        update();
    });
}

/*! Switches to the following month
 * \brief CalendarWidget::showNextMonth
 */
void CalendarWidget::showNextMonth()
{
    int year = m_curDate->year();
    int month = m_curDate->month();
    if(year == 2200 && month == 12) return;
    if(month == 12)
    {
        month = 1;
        year++;
    }
    else
    {
        month++;
    }
    m_curDate->setDate(year, month, 5);
    deleteMonthGroupBox();
}

/*! Switches to previous month
 * \brief CalendarWidget::showPrevMonth
 */
void CalendarWidget::showPrevMonth()
{
    int year = m_curDate->year();
    int month = m_curDate->month();
    if(year == 1900 && month == 1) return;
    if(month == 1)
    {
        month = 12;
        year--;
    }
    else
    {
        month--;
    }
    m_curDate->setDate(year, month, 5);
    deleteMonthGroupBox();
}
