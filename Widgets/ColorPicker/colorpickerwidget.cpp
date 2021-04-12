#include "colorpickerwidget.h"
#include "Widgets/colorpickermodiswidget.h"
#include "Utils/colorpickerconstants.h"
#include "Widgets/Edits/hexedit.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QDebug>

ColorPickerWidget::ColorPickerWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setSpacing(1);
    QHBoxLayout* headerLayout = new QHBoxLayout;
    headerLayout->setSpacing(1);
    QHBoxLayout* resLayout = new QHBoxLayout;
    resLayout->setSpacing(1);
    QHBoxLayout* footerLayout = new QHBoxLayout;
    footerLayout->setSpacing(1);
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(1);
    QPushButton* sliderBtn = new QPushButton("Slider");
    QPushButton* spectrumBtn = new QPushButton("Spectrum");

    QSpacerItem* hSpacer = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* hSpacer2 = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* hSpacer3 = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* hSpacerL = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* hSpacerR = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* vSpacerT = new QSpacerItem(50, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem* vSpacerB = new QSpacerItem(50, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

    m_modi = new ColorPickerModisWidget;
    m_hexEdit = new HexEdit("#000000");
    m_hexEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QPushButton* cancelBtn = new QPushButton("Cancel");
    QPushButton* applyBtn = new QPushButton("Apply");
    m_resBtn = new QPushButton;
    m_resBtn->setDisabled(true);
    headerLayout->addItem(hSpacer);
    headerLayout->addWidget(sliderBtn);
    headerLayout->addWidget(spectrumBtn);
    headerLayout->addItem(hSpacer2);
    layout->addItem(vSpacerT);
    layout->addLayout(headerLayout);
    layout->addWidget(m_modi);
    resLayout->addWidget(m_resBtn);
    resLayout->addWidget(m_hexEdit);
    layout->addLayout(resLayout);
    footerLayout->addItem(hSpacer3);
    footerLayout->addWidget(cancelBtn);
    footerLayout->addWidget(applyBtn);
    layout->addLayout(footerLayout);
    layout->addItem(vSpacerB);
    mainLayout->addItem(hSpacerL);
    mainLayout->addLayout(layout);
    mainLayout->addItem(hSpacerR);
    connect(cancelBtn, &QPushButton::clicked, this, &ColorPickerWidget::closeWidget);
    connect(applyBtn, &QPushButton::clicked, [this]()
    {
        emit colorChanged(m_color);
        emit closeWidget();
    });
    connect(m_modi, &ColorPickerModisWidget::colorChanged, [this](const QColor& c)
    {
        m_color = c;
        m_resBtn->setStyleSheet("QPushButton{ background-color: rgba(" +
                              QString::number(c.red()) + ", " + QString::number(c.green()) +
                              ", " + QString::number(c.blue()) + ", 255)}");
        m_hexEdit->setText(c.name());
    });
    connect(m_hexEdit, &HexEdit::editingFinished, [this]()
    {
        m_modi->setColor(QColor(m_hexEdit->text()));
    });
    connect(sliderBtn, &QPushButton::clicked, [this]()
    {
        m_modi->setCurrentIndex(SliderModus);
    });
    connect(spectrumBtn, &QPushButton::clicked, [this]()
    {
        m_modi->setCurrentIndex(SpectrumModus);
        m_modi->updateSpectrum();
    });
}

//SLOTS**************************************************************
void ColorPickerWidget::setColor(const QColor &color)
{
    m_color = color;
    m_modi->setColor(color);
    m_hexEdit->setText(color.name());
    m_resBtn->setStyleSheet("QPushButton{ background-color: rgba(" +
                          QString::number(color.red()) + ", " + QString::number(color.green()) +
                          ", " + QString::number(color.blue()) + ", 255)}");
}
