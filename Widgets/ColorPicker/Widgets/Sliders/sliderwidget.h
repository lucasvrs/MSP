#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H

#include <QWidget>

class AllSlidersWidget;

class SliderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SliderWidget(QWidget *parent = nullptr);

private:
    AllSlidersWidget* m_sliders;

signals:
    void colorChanged(const QColor& color);

public slots:
    void setColor(const QColor& color);
};

#endif // SLIDERWIDGET_H
