#include "daygroupbox.h"
#include <QDate>
#include <QGridLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QFrame>
#include <QPainter>
#include <QPaintEngine>
#include <QDomElement>
#include "Xml/xmlreader.h"
#include "appointmentgroupbox.h"

DayGroupBox::DayGroupBox(const QDate& date, bool mainMonth, QWidget *parent) :
    QGroupBox(parent),
    m_mainMonth(mainMonth)
{
    //defines style and attributes
    m_date = new QDate(date);
    (date == QDate::currentDate()) ? m_defPalette = curDayPalette() :
            m_defPalette = QPalette(QColor(255, 255, 255));
    if(!mainMonth) m_defPalette = otherMonthPalette();
    setPalette(m_defPalette);
    m_layout = new QGridLayout(this);
    setAutoFillBackground(true);
    setMouseTracking(true);
    addAppointments();
}

const QDate& DayGroupBox::date() const
{
    return *m_date;
}

/*! Adds appointment widgets
 * \brief DayGroupBox::addAppointments
 */
void DayGroupBox::addAppointments()
{
    removeLayout();
    QFont font("Agency FB", 11);
    QLabel* dayLabel = new QLabel(QString::number(m_date->day()));
    dayLabel->setFont(font);
    dayLabel->setAlignment(Qt::AlignCenter);
    m_layout->addWidget(dayLabel);
    int counter = 1;
    for(QString str : allAppointments())
    {
        if(!m_mainMonth)
        {
            break;
        }
        if(counter == 2)
        {
            if(allAppointments().size() == 2)
            {
                AppointmentGroupBox* app = new AppointmentGroupBox(str);
                m_layout->addWidget(app);
                break;
            }
            AppointmentGroupBox* app = new AppointmentGroupBox("...");
            m_layout->addWidget(app);
            break;
        }
        AppointmentGroupBox* app = new AppointmentGroupBox(str);
        m_layout->addWidget(app);
        counter++;
    }
    //QSpacerItem* vSpacer = new QSpacerItem(1, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    //m_layout->addItem(vSpacer, 5, 0);
}

/*! Removes layout
 * \brief DayGroupBox::removeLayout
 */
void DayGroupBox::removeLayout()
{
    for(int i = m_layout->count() - 1; i > -1; i--)
    {
        QLayoutItem* item = m_layout->takeAt(i);
        delete item->widget();
        delete item;
    }
}

double DayGroupBox::height() const{return m_height;}

void DayGroupBox::setHeight(double height){m_height = height;}

void DayGroupBox::setWidth(double width){m_width = width;}

double DayGroupBox::width() const{return m_width;}

QPalette DayGroupBox::curDayPalette() const
{
    QPalette p;
    p.setColor(QPalette::Window, QColor(0, 255, 0));
    return p;
}

QPalette DayGroupBox::hoverPalette() const
{
    QPalette p;
    p.setColor(QPalette::Window, QColor(255, 160, 160));
    return p;
}

QPalette DayGroupBox::otherMonthPalette() const
{
    QPalette p;
    p.setColor(QPalette::Window, QColor(200, 200, 200));
    return p;
}

QPalette DayGroupBox::pressedPalette() const
{
    QPalette p;
    p.setColor(QPalette::Window, QColor(255, 0, 0));
    return p;
}

/*! Reads all appointments out of a xml file
 * \brief DayGroupBox::allAppointments
 * \return
 */
QStringList DayGroupBox::allAppointments()
{
    QStringList strList;
    XMLReader reader("./../Kalender/appointments.xml");
    QDomElement year = reader.findElemUnderRoot("year", "id", QString::number(m_date->year()));
    QDomElement month = reader.findElemUnderElem(year, "month", "id", QString::number(m_date->month()));
    QDomElement day = reader.findElemUnderElem(month, "day", "id", QString::number(m_date->day()));
    for(QDomElement elem : *reader.allElemsUnderElem(day))
    {
        strList.append(elem.text());
    }
    return strList;
}

//EVENTS*****************************************************************
void DayGroupBox::enterEvent(QEvent* e)
{
    setPalette(hoverPalette());
    QGroupBox::enterEvent(e);
}

void DayGroupBox::leaveEvent(QEvent* e)
{
    setPalette(m_defPalette);
    QGroupBox::leaveEvent(e);
}

void DayGroupBox::mousePressEvent(QMouseEvent* e)
{
    setPalette(pressedPalette());
    QGroupBox::mousePressEvent(e);
}

void DayGroupBox::mouseReleaseEvent(QMouseEvent* e)
{
    setPalette(m_defPalette);
    QGroupBox::mouseReleaseEvent(e);
    emit clicked(*m_date);
}

void DayGroupBox::paintEvent(QPaintEvent* e)
{
    QGroupBox::paintEvent(e);
}
