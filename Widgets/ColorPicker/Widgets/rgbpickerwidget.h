#ifndef RGBPICKERWIDGET_H
#define RGBPICKERWIDGET_H

#include <QWidget>

class SlideEditConnectWidget;

class RgbPickerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RgbPickerWidget(QWidget *parent = nullptr);

private:
    int m_v[3];
    SlideEditConnectWidget* m_edits[3];

signals:
    void colorChanged(const QColor& color);

public slots:
    void setColor(const QColor& color);
};

#endif // RGBPICKERWIDGET_H
