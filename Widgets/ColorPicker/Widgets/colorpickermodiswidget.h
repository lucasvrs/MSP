#ifndef COLORPICKERMODISWIDGET_H
#define COLORPICKERMODISWIDGET_H

#include <QStackedWidget>

class SliderWidget;
class ColorSpectrumWidget;

class ColorPickerModisWidget : public QStackedWidget
{
    Q_OBJECT

public:
    ColorPickerModisWidget(QWidget* parent = nullptr);

private:
    SliderWidget* m_sliders;
    ColorSpectrumWidget* m_spectrum;

signals:
    void colorChanged(const QColor& color);

public slots:
    void setColor(const QColor& color);
    void updateSpectrum();
};

#endif // COLORPICKERMODISWIDGET_H
