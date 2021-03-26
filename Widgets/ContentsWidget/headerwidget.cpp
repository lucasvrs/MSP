#include "headerwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

HeaderWidget::HeaderWidget(QWidget *parent) : QWidget(parent)
{
    //defines layout
    QHBoxLayout* layout = new QHBoxLayout(this);
    m_headerLabel = new QLabel("Contents");
    QPushButton* optionsBtn = new QPushButton("Options");
    QSpacerItem* hSpacerL = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* hSpacerR = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addItem(hSpacerL);
    layout->addWidget(m_headerLabel);
    layout->addItem(hSpacerR);
    layout->addWidget(optionsBtn);
}

/*! Sets text of header label
 * \brief HeaderWidget::setHeader
 * \param title - text
 */
void HeaderWidget::setHeader(const QString& title)
{
    m_headerLabel->setText(title);
}
