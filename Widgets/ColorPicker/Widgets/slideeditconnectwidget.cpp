#include "slideeditconnectwidget.h"
#include "Sliders/responsiveslider.h"
#include "Edits/regexedit.h"
#include <QHBoxLayout>
#include <QDebug>

SlideEditConnectWidget::SlideEditConnectWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    m_slider = new ResponsiveSlider(Qt::Horizontal);
    m_edit = new RegexEdit;
    layout->addWidget(m_slider);
    layout->addWidget(m_edit);
    connect(m_edit, &RegexEdit::editingFinished, [this]()
    {
        int v = m_edit->text().toInt();
        m_slider->setValue(v);
        emit valueChanged(v);
    });
    connect(m_slider, &ResponsiveSlider::valueChanged, [this]()
    {
        m_edit->setText(QString::number(m_slider->value()));
        emit valueChanged(m_slider->value());
    });
}

//SLOTS*******************************************************
void SlideEditConnectWidget::setRange(int min, int max)
{
    m_slider->setRange(min, max);
}

void SlideEditConnectWidget::setRegex(const QString& regex)
{
    m_edit->setRegex(regex);
}

void SlideEditConnectWidget::setStart(int v)
{
    m_edit->setText(QString::number(v));
    m_slider->setValue(v);
}

void SlideEditConnectWidget::setSliderStyleSheet(const QString& str)
{
    m_slider->setStyleSheet(str);
}

void SlideEditConnectWidget::setValue(int v)
{
    m_slider->blockSignals(true);
    m_slider->setValue(v);
    m_edit->setText(QString::number(m_slider->value()));
    m_slider->blockSignals(false);
}
