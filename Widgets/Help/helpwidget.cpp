#include "helpwidget.h"
#include "mainhelpwidget.h"
#include "subjecthelpwidget.h"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>

/*!
 * \brief Constructor
 * \param parent
 */
HelpWidget::HelpWidget(QWidget *parent) : QStackedWidget(parent), s(nullptr)
{
    w = new MainHelpWidget;
    addWidget(w);
    //setCurrentIndex(0);
    connect(w,&MainHelpWidget::emitSignal,this,&HelpWidget::changeSite);
}
/*!
 * \brief changes Site
 * \param item WidgetItem which is shown
 */
void HelpWidget::changeSite(WidgetItem *item)
{

    s = new SubjectHelpWidget(item);
    addWidget(s);
    connect(s,&SubjectHelpWidget::emitSignal, this, &HelpWidget::homeScreen);
    setCurrentIndex(1);
    s->setWidth(width());
    s->update();

}
/*!
 * \brief switch to homescreen
 */
void HelpWidget::homeScreen()
{
   removeWidget(currentWidget());
   setCurrentIndex(0);
}

//EVENTS************************************
void HelpWidget::resizeEvent(QResizeEvent *e)
{
    QStackedWidget::resizeEvent(e);
    w->setWidth(width());
    //w->setHeight(height());
   if(s != nullptr)
   {
       s->setWidth(width());
   }
}





