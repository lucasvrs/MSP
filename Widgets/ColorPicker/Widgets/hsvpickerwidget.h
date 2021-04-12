#ifndef HSVPICKERWIDGET_H
#define HSVPICKERWIDGET_H

#include <QWidget>

class SlideEditConnectWidget;

class HsvPickerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HsvPickerWidget(QWidget *parent = nullptr);

private:
    int m_v[3];
    SlideEditConnectWidget* m_edits[3];

signals:
    void colorChanged(const QColor& color);

public slots:
    void setColor(const QColor& color);
};

#endif // HSVPICKERWIDGET_H
