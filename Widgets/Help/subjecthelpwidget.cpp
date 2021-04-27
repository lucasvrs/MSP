#include "subjecthelpwidget.h"
#include "subjecthelpcontentswidget.h"
#include <QDebug>
/*!
 * \brief Constructor
 * \param item widgteitem which is shown
 * \param parent
 */
SubjectHelpWidget::SubjectHelpWidget( WidgetItem *item,QWidget *parent) : QScrollArea(parent)
{
    m_subject = new SubjectHelpContentsWidget(item);
    setWidget(m_subject);
    connect(m_subject, &SubjectHelpContentsWidget::emitSignal,this,&SubjectHelpWidget::emitSignal);
}
/*!
 * \brief set width of widget
 * \param width
 */
void SubjectHelpWidget::setWidth(double width)
{
     m_subject->setWidth(width);
}
