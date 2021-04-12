#include "colorpickermodiswidget.h"
#include "Sliders/sliderwidget.h"
#include "Spectrum/Widgets/colorspectrumwidget.h"

ColorPickerModisWidget::ColorPickerModisWidget(QWidget *parent) :
    QStackedWidget(parent)
{
    m_sliders = new SliderWidget;
    m_spectrum = new ColorSpectrumWidget;
    addWidget(m_sliders);
    addWidget(m_spectrum);
    connect(m_sliders, &SliderWidget::colorChanged, [this](const QColor& color)
    {
        m_spectrum->setColor(color);
        emit colorChanged(color);
    });
    connect(m_spectrum, &ColorSpectrumWidget::colorChanged, [this](const QColor& color)
    {
        m_sliders->setColor(color);
        emit colorChanged(color);
    });
}

//SLOTS*************************************************************++
void ColorPickerModisWidget::setColor(const QColor &color)
{
    m_sliders->setColor(color);
    m_spectrum->setColor(color);
}

void ColorPickerModisWidget::updateSpectrum()
{
    m_spectrum->updateSpectrum();
}
