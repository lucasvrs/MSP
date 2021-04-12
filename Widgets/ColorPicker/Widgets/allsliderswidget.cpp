#include "allsliderswidget.h"
#include "rgbpickerwidget.h"
#include "hsvpickerwidget.h"
#include <QPushButton>

AllSlidersWidget::AllSlidersWidget(QWidget *parent) : QStackedWidget(parent)
{
    m_rgb = new RgbPickerWidget;
    m_hsv = new HsvPickerWidget;
    addWidget(m_rgb);
    addWidget(m_hsv);
    connect(m_rgb, &RgbPickerWidget::colorChanged, [this](const QColor& c)
    {
        m_hsv->setColor(c);
        emit colorChanged(c);
    });
    connect(m_hsv, &HsvPickerWidget::colorChanged, [this](const QColor& c)
    {
        m_rgb->setColor(c);
        emit colorChanged(c);
    });
}

void AllSlidersWidget::setColor(const QColor &color)
{
    m_rgb->setColor(color);
    m_hsv->setColor(color);
}
