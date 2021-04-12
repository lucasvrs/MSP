#include "hsvpickerwidget.h"
#include "slideeditconnectwidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>

HsvPickerWidget::HsvPickerWidget(QWidget *parent) : QWidget(parent), m_v{0, 0, 0}
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel("HSV");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    for(int i = 0; i < 3; i++)
    {
        SlideEditConnectWidget* widget = new SlideEditConnectWidget;
        m_edits[i] = widget;
        if(i == 0) widget->setSliderStyleSheet("QSlider::handle:horizontal{ background: green; border-radius: 6px;}");
        if(i == 1) widget->setSliderStyleSheet("QSlider::handle:horizontal{ background: red; border-radius: 6px;}");
        if(i == 2) widget->setSliderStyleSheet("QSlider::handle:horizontal{ background: black; border-radius: 6px;}");
        widget->setRange(0, 255);
        if(i == 1 || i == 2) widget->setRegex("0|[1-9][0-9]|1[0-9]{1,2}|2[0-4][0-9]|25[0-5]");
        if(i == 0)
        {
            widget->setRegex("0|[1-9][0-9]|1[0-9]{1,2}|2[0-9][0-9]|3[0-5][0-9]");
            widget->setRange(0, 359);
        }
        widget->setStart(0);
        layout->addWidget(widget);
        connect(widget, &SlideEditConnectWidget::valueChanged, [this, i](int v)
        {
            m_v[i] = v;
            QColor c;
            c.setHsv(m_v[0], m_v[1], m_v[2]);
            emit colorChanged(c);
        });
    }
}

void HsvPickerWidget::setColor(const QColor &color)
{
    int value = 0;
    for(int i = 0; i < 3; i++)
    {
        if(i == 0) value = color.hsvHue();
        if(i == 1) value = color.hsvSaturation();
        if(i == 2) value = color.value();
        m_v[i] = value;
        m_edits[i]->setValue(value);
    }
}
