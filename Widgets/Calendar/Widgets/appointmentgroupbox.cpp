/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "appointmentgroupbox.h"
#include <QHBoxLayout>
#include <QLabel>

AppointmentGroupBox::AppointmentGroupBox(const QString& title, QWidget* parent) :
    QGroupBox(parent)
{
    setObjectName("appointmentBox");

    QHBoxLayout* layout = new QHBoxLayout(this);

    QLabel* label = new QLabel(title);
    label->setAlignment(Qt::AlignCenter);

    //define layout
    layout->addWidget(label);
}
