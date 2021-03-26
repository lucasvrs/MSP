#include "interfaceoptionswidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

InterfaceOptionsWidget::InterfaceOptionsWidget(QWidget *parent) : QWidget(parent)
{
    //defines layout
    QGridLayout* layout = new QGridLayout(this);

    QLabel* themeLabel = new QLabel("Theme");
    themeLabel->setAlignment(Qt::AlignCenter);

    QPushButton* lightModeBtn = new QPushButton("Light");
    QPushButton* darkModeBtn = new QPushButton("Dark");

    QSpacerItem* hThemeSpacerL = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* hThemeSpacerR = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

    layout->addWidget(themeLabel, 0, 0, 1, 4);
    layout->addItem(hThemeSpacerL, 1, 0, 1, 1);
    layout->addWidget(lightModeBtn, 1, 1, 1, 1);
    layout->addWidget(darkModeBtn, 1, 2, 1, 1);
    layout->addItem(hThemeSpacerR, 1, 3, 1, 1);
}
