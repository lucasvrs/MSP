/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "mspwidget.h"
#include "Options/optionswidget.h"
#include "ContentsWidget/contentswidget.h"

MspWidget::MspWidget(QWidget *parent) : QStackedWidget(parent)
{
    ContentsWidget* contents = new ContentsWidget;
    m_options = new OptionsWidget;
    addWidget(contents);
    addWidget(m_options);
    connect(contents, &ContentsWidget::showOptions, [this]()
    {
        setCurrentIndex(1);
    });
    connect(m_options, &OptionsWidget::closeOptions, [this]()
    {
        setCurrentIndex(0);
    });
    connect(m_options, &OptionsWidget::changeStyle, this, &MspWidget::changeStyle);
}
