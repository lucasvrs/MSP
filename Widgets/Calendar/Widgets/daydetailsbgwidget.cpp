#include "daydetailsbgwidget.h"
#include "daydetailsgroupbox.h"
#include <QGraphicsOpacityEffect>
#include <QGridLayout>
#include <QSpacerItem>
#include <QMouseEvent>
#include <QDebug>

DayDetailsBgWidget::DayDetailsBgWidget(const QDate& date, QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("DayDetailsBgWidget{background-color: rgba(0, 0, 0, 150);}");

    //define layout
    QGridLayout* layout = new QGridLayout(this);
    QSpacerItem* hItemL = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* hItemR = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* vItemT = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem* vItemB = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_details = new DayDetailsGroupBox(date);
    layout->addItem(vItemT, 0, 1);
    layout->addItem(hItemL, 1, 0);
    layout->addWidget(m_details, 1, 1);
    layout->addItem(hItemR, 1, 2);
    layout->addItem(vItemB, 2, 1);

    //add connects
    connect(m_details, &DayDetailsGroupBox::needsUpdate, this, &DayDetailsBgWidget::needsUpdate);
}

//EVENTS********************************************************************************
void DayDetailsBgWidget::mouseReleaseEvent(QMouseEvent* e)
{
    QWidget::mouseReleaseEvent(e);
    QPoint pos = e->pos();
    QPoint detailsPos = m_details->pos();
    double width = m_details->width();
    double height = m_details->height();
    if(pos.x() > detailsPos.x() && pos.x() < detailsPos.x() + width && pos.y() > detailsPos.y() && pos.y() < detailsPos.y() + height) return;
    emit clicked();
}
