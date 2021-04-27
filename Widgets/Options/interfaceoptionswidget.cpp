/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "interfaceoptionswidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

InterfaceOptionsWidget::InterfaceOptionsWidget(QWidget *parent) : QWidget(parent)
{
    //defines layout
    QGridLayout* layout = new QGridLayout(this);
    QHBoxLayout* hLayout = new QHBoxLayout;

    QLabel* themeLabel = new QLabel("Theme");
    themeLabel->setAlignment(Qt::AlignCenter);

    QPushButton* lightModeBtn = new QPushButton("Light");
    QPushButton* darkModeBtn = new QPushButton("Dark");
    QPushButton* saveBtn = new QPushButton("Save");
    QPushButton* cancelBtn = new QPushButton("Cancel");

    QSpacerItem* hThemeSpacerL = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* hThemeSpacerR = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* hExitSpacerL = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* vSpacerB = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout->addWidget(themeLabel, 0, 0, 1, 4);
    layout->addItem(hThemeSpacerL, 1, 0, 1, 1);
    layout->addWidget(lightModeBtn, 1, 1, 1, 1);
    layout->addWidget(darkModeBtn, 1, 2, 1, 1);
    layout->addItem(hThemeSpacerR, 1, 3, 1, 1);
    layout->addItem(vSpacerB, 2, 1);
    layout->addLayout(hLayout, 3, 0, 1, 4);
    hLayout->addItem(hExitSpacerL);
    hLayout->addWidget(cancelBtn);
    hLayout->addWidget(saveBtn);

    connect(cancelBtn, &QPushButton::clicked, this, &InterfaceOptionsWidget::closeOptions);
    connect(lightModeBtn, &QPushButton::clicked, [this]()
    {
        emit changeStyle(0);
    });
    connect(darkModeBtn, &QPushButton::clicked, [this]()
    {
        emit changeStyle(1);
    });
}
