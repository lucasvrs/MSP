#include "sliderwidget.h"
#include "Widgets/ColorPicker/Widgets/allsliderswidget.h"
#include "Widgets/ColorPicker/Utils/colorpickerconstants.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

SliderWidget::SliderWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QHBoxLayout* headerLayout = new QHBoxLayout;
    QPushButton* rgbBtn = new QPushButton("RGB");
    QPushButton* hsvBtn = new QPushButton("HSV");
    QSpacerItem* hSpacer = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* hSpacer2 = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    headerLayout->addItem(hSpacer);
    headerLayout->addWidget(rgbBtn);
    headerLayout->addWidget(hsvBtn);
    headerLayout->addItem(hSpacer2);
    layout->addLayout(headerLayout);
    m_sliders = new AllSlidersWidget;
    layout->addWidget(m_sliders);
    connect(m_sliders, &AllSlidersWidget::colorChanged, this, &SliderWidget::colorChanged);
    connect(rgbBtn, &QPushButton::clicked, [this]()
    {
        m_sliders->setCurrentIndex(RgbSlider);
    });
    connect(hsvBtn, &QPushButton::clicked, [this]()
    {
        m_sliders->setCurrentIndex(HsvSlider);
    });
}

void SliderWidget::setColor(const QColor &color)
{
    m_sliders->setColor(color);
}
