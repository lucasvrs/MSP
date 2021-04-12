#include "spectrumpalettewidget.h"
#include "Widgets/ColorPicker/Widgets/Spectrum/Utils/colorspectrum.h"
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>

SpectrumPaletteWidget::SpectrumPaletteWidget(QWidget *parent) : QWidget(parent), m_selectedBtn(nullptr)
{
    QGridLayout* layout = new QGridLayout(this);
    int row = 0;
    int col = 0;
    const long double f1 = 1.0 / 400;
    const long double f2 = 1.0 / 780;
    for(int i = 0; i < LIMIT; i++)
    {
        if(row == LIMIT / 5)
        {
            row = 0;
            col++;
        }
        m_btns[i] = new QPushButton;
        m_btns[i]->setFixedHeight(50);
        long double freq = ColorSpectrum::linMap(0, i + 1, LIMIT, f1, f2);
        QColor c = ColorSpectrum::waveLengthToColor(1.0 / freq);
        setBtnStylesheet(m_btns[i], c, Qt::black);
        layout->addWidget(m_btns[i], row, col);
        connect(m_btns[i], &QPushButton::clicked, [this, i, c]()
        {
            if(m_selectedBtn != nullptr) setBtnStylesheet(m_selectedBtn, m_selectedColor, Qt::black);
            setBtnStylesheet(m_btns[i], c, Qt::red);
            m_selectedBtn = m_btns[i];
            m_selectedColor = c;
            emit colorChanged(c);
        });
        row++;
    }
}

void SpectrumPaletteWidget::setBtnStylesheet(QPushButton* btn, const QColor& c, const QColor& bC)
{
    btn->setStyleSheet("QPushButton{background-color: rgba(" + QString::number(c.red()) +
                             ", " + QString::number(c.green()) + ", " + QString::number(c.blue()) +
                             ", 255); border: 2px solid rgba(" + QString::number(bC.red()) +
                       ", " + QString::number(bC.green()) + ", " + QString::number(bC.blue()) +
                       ", 255);}");
}

//SLOTS***********************************************************************
void SpectrumPaletteWidget::setColor(const QColor& color)
{
    if(m_selectedBtn != nullptr) setBtnStylesheet(m_selectedBtn, m_selectedColor, Qt::black);
    for(QPushButton* btn : m_btns)
    {
        if(color == btn->palette().color(QPalette::Window))
        {
            setBtnStylesheet(btn, color, Qt::red);
            m_selectedBtn = btn;
            m_selectedColor = color;
            return;
        }
    }
}
