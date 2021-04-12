#ifndef COLORPICKERWIDGET_H
#define COLORPICKERWIDGET_H

#include <QWidget>

class ColorPickerModisWidget;
class QPushButton;
class HexEdit;

class ColorPickerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorPickerWidget(QWidget *parent = nullptr);

private:
    QColor m_color;
    ColorPickerModisWidget* m_modi;
    QPushButton* m_resBtn;
    HexEdit* m_hexEdit;

signals:
    void colorChanged(const QColor& color);
    void closeWidget();

public slots:
    void setColor(const QColor& color);
};

#endif // COLORPICKERWIDGET_H
