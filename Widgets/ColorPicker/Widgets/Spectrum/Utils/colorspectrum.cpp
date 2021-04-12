#include "colorspectrum.h"
#include <QPainter>
#include <array>
#include <QDebug>

long double ColorSpectrum::linMap(double x1, double x, double x2, double y1, double y2)
{
    return y1 + (y1 - y2) * (x - x1) / (x1 - x2);
}

QColor ColorSpectrum::waveLengthToColor(double l)
{
    std::array<Threshold, 8 > thresholds {
        Threshold{380, 420, nullptr, [](double x){ return 0.3 + 0.7 * x; }},
        Threshold{380, 440, [](double x){return CustomColor{1 - x, 0, 1}; }},
        Threshold{440, 490, [](double x){return CustomColor{0, x, 1}; }},
        Threshold{490, 510, [](double x){return CustomColor{0, 1, 1 - x}; }},
        Threshold{510, 580, [](double x){return CustomColor{x, 1, 0}; }},
        Threshold{580, 645, [](double x){return CustomColor{1, 1 - x, 0}; }},
        Threshold{645, 780, [](double){return CustomColor{1, 0, 0}; }},
        Threshold{700, 780, nullptr, [](double x){return 1 - 0.7 * x; }}
    };

    CustomColor color;
    double factor = 1.0;
    for(auto &thr : thresholds)
    {
        if(l < thr.begin || l >= thr.end) continue;
        auto x = linMap(thr.begin, l, thr.end);
        if(thr.factor) factor = thr.factor(x);
        if(thr.color) color = thr.color(x);
    }
    return color.toColor(factor);
}

int ColorSpectrum::findColor(int w, const QColor &color)
{
    for(int x = 0; x < w; x++)
    {
        const long double f1 = 1.0 / 400;
        const long double f2 = 1.0 / 780;
        long double freq = linMap(0, x, w, f1, f2);
        QColor cC = waveLengthToColor(1.0 / freq);
        if(cC == color) return x;
    }
    return w / 2;
}

QPixmap ColorSpectrum::spectrum(int w, int h)
{
    QPixmap map(w, h);
    QPainter p(&map);
    for(int x = 0; x < w; x++)
    {
        const long double f1 = 1.0 / 400;
        const long double f2 = 1.0 / 780;
        long double freq = linMap(0, x, w, f1, f2);
        p.setPen(waveLengthToColor(1.0 / freq));
        p.drawLine(x, 0, x, h);
    }
    return map;
}
