#include "mspwidget.h"
#include "Options/optionswidget.h"
#include "ContentsWidget/contentswidget.h"

MspWidget::MspWidget(QWidget *parent) : QStackedWidget(parent)
{
    //defines layout
    ContentsWidget* contents = new ContentsWidget;
    m_options = new OptionsWidget;
    addWidget(contents);
    addWidget(m_options);
}
