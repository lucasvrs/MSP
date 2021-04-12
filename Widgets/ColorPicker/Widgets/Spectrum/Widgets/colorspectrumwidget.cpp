#include "colorspectrumwidget.h"
#include "spectrumsview.h"
#include "Widgets/ColorPicker/Widgets/Spectrum/Scene/spectrumscene.h"
#include "Widgets/ColorPicker/Widgets/Spectrum/Utils/colorspectrum.h"
#include "spectrumpalettewidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

ColorSpectrumWidget::ColorSpectrumWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    m_view = new SpectrumsView;
    m_scene = new SpectrumScene(m_view->width(), ColorSpectrum::spectrum(m_view->width(),m_view->height()));
    m_view->setScene(m_scene);
    m_palette = new SpectrumPaletteWidget;
    layout->addWidget(m_view);
    layout->addWidget(m_palette);
    connect(m_scene, &SpectrumScene::colorChanged, [this](const QColor& c)
    {
        m_palette->setColor(c);
        emit colorChanged(c);
    });
    connect(m_palette, &SpectrumPaletteWidget::colorChanged, [this](const QColor& c)
    {
        m_scene->setColor(c);
        emit colorChanged(c);
    });
}

//EVENTS************************************************************
void ColorSpectrumWidget::resizeEvent(QResizeEvent* e)
{
    QWidget::resizeEvent(e);
    m_scene->updateScene(m_view->width(), ColorSpectrum::spectrum(m_view->width(), m_view->height()));
    m_view->centerOn(m_view->width()/2, m_view->height()/2);
}

//SLOTS*************************************************************
void ColorSpectrumWidget::setColor(const QColor& color)
{
    m_scene->setColor(color);
}

void ColorSpectrumWidget::updateSpectrum()
{
    m_scene->updateScene(m_view->width(), ColorSpectrum::spectrum(m_view->width(), m_view->height()));
    m_view->centerOn(m_view->width()/2, m_view->height()/2);
}
