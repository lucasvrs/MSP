/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "optionswidget.h"
#include "interfaceoptionswidget.h"

OptionsWidget::OptionsWidget(QWidget *parent) : QTabWidget(parent)
{
    //defines layout
    m_interface = new InterfaceOptionsWidget;
    addTab(m_interface, "Interface");

    connect(m_interface, &InterfaceOptionsWidget::closeOptions, this, &OptionsWidget::closeOptions);
}
