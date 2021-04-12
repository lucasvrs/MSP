#ifndef RESPONSIVESLIDER_H
#define RESPONSIVESLIDER_H

#include <QSlider>

class ResponsiveSlider : public QSlider
{
public:
    ResponsiveSlider(Qt::Orientation orientation, QWidget *parent = nullptr);
    ResponsiveSlider(QWidget *parent = nullptr);
};

#endif // RESPONSIVESLIDER_H
