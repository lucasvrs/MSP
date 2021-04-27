#include "mainhelpwidget.h"
#include "mainhelpcontentswidget.h"
#include "widgetitem.h"
/*!
 * \brief Constructor
 * \param parent
 */
MainHelpWidget::MainHelpWidget(QWidget *parent) : QScrollArea(parent)
{
    m_main= new MainHelpContentsWidget;
    setWidget(m_main);
    connect(m_main, &MainHelpContentsWidget::emitSignal,this,&MainHelpWidget::emitSignal);
}

//SLOTS*******************************
void MainHelpWidget::setWidth(double width)
{
    m_main->setWidth(width);
}

void MainHelpWidget::setHeight(double height)
{
    m_main->setHeight(height);
}
