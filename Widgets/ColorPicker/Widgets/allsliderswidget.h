#ifndef ALLSLIDERSWIDGET_H
#define ALLSLIDERSWIDGET_H

#include <QStackedWidget>

class RgbPickerWidget;
class HsvPickerWidget;

class AllSlidersWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit AllSlidersWidget(QWidget *parent = nullptr);

private:
    RgbPickerWidget* m_rgb;
    HsvPickerWidget* m_hsv;

signals:
    void colorChanged(const QColor& color);

public slots:
    void setColor(const QColor& color);
};

#endif // ALLSLIDERSWIDGET_H
