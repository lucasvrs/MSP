#ifndef SPECTRUMPALETTEWIDGET_H
#define SPECTRUMPALETTEWIDGET_H

#include "Widgets/ColorPicker/Widgets/Spectrum/Utils/spectrumconstants.h"
#include <QWidget>

class QPushButton;

class SpectrumPaletteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SpectrumPaletteWidget(QWidget *parent = nullptr);

private:
    QPushButton* m_btns[LIMIT];
    QPushButton* m_selectedBtn;
    QColor m_selectedColor;
    void setBtnStylesheet(QPushButton* btn, const QColor& c, const QColor& bC);

signals:
    void colorChanged(const QColor& color);

public slots:
    void setColor(const QColor& color);
};

#endif // SPECTRUMPALETTEWIDGET_H
