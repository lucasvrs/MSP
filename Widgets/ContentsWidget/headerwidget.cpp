/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "headerwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

HeaderWidget::HeaderWidget(QWidget *parent) : QWidget(parent), m_prevWidget(nullptr)
{
    //defines layout
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    m_headerLabel = new QLabel("Subjects");
    m_prevBtn = new QPushButton("Previous");
    m_prevBtn->setDisabled(true);
    QPushButton* optionsBtn = new QPushButton("Options");
    QSpacerItem* hSpacerL = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* hSpacerR = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addWidget(m_prevBtn);
    layout->addItem(hSpacerL);
    layout->addWidget(m_headerLabel);
    layout->addItem(hSpacerR);
    layout->addWidget(optionsBtn);
    connect(optionsBtn, &QPushButton::clicked, [this]()
    {
        emit showOptions();
    });
    connect(m_prevBtn, &QPushButton::clicked, [this]()
    {
        if(m_prevWidget != nullptr)
        {
            m_prevBtn->setDisabled(true);
            emit showWidget(m_prevWidget);
        }
    });
}

/*! Sets text of header label
 * \brief HeaderWidget::setHeader
 * \param title - text
 */
void HeaderWidget::setHeader(const QString& title)
{
    m_headerLabel->setText(title);
}

void HeaderWidget::setPrevWidget(QWidget* w)
{
    m_prevWidget = w;
    m_prevBtn->setDisabled(false);
}

void HeaderWidget::disablePrev()
{
    m_prevWidget = nullptr;
    m_prevBtn->setDisabled(true);
}
