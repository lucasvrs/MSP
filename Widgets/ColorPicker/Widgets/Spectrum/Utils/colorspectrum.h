#ifndef COLORSPECTRUM_H
#define COLORSPECTRUM_H

#include <QColor>
#include <QPixmap>

struct CustomColor
{
    double red = 0., green = 0., blue = 0.;
    QColor toColor(double fac)
    {
        auto const map = [fac](double c) -> double {
            double gamma = 0.8;
            return pow(c * fac, gamma);
        };
        return QColor::fromRgbF(map(red), map(green), map(blue));
    }
};

struct Threshold
{
    double begin, end;
    CustomColor (*color)(double);
    double (*factor)(double) = nullptr;
};

class ColorSpectrum
{
public:
    ColorSpectrum() = default;
    static long double linMap(double x1, double x, double x2, double y1 = 0., double y2 = 1.);
    static QColor waveLengthToColor(double l);
    static int findColor(int w, const QColor& color);
    static QPixmap spectrum(int w, int h);
};

#endif // COLORSPECTRUM_H
