#ifndef SLIDEEDITCONNECTWIDGET_H
#define SLIDEEDITCONNECTWIDGET_H

#include <QWidget>

class ResponsiveSlider;
class RegexEdit;

class SlideEditConnectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SlideEditConnectWidget(QWidget *parent = nullptr);

private:
    ResponsiveSlider* m_slider;
    RegexEdit* m_edit;

signals:
    void valueChanged(int v);

public slots:
    void setRange(int min, int max);
    void setRegex(const QString& regex);
    void setStart(int v);
    void setSliderStyleSheet(const QString& str);
    void setValue(int v);
};

#endif // SLIDEEDITCONNECTWIDGET_H
