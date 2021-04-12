#ifndef COLORSPECTRUMWIDGET_H
#define COLORSPECTRUMWIDGET_H

#include <QObject>
#include <QWidget>

class SpectrumsView;
class SpectrumScene;
class QGraphicsPixmapItem;
class QPushButton;
class SpectrumPaletteWidget;

class ColorSpectrumWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorSpectrumWidget(QWidget *parent = nullptr);

private:
    SpectrumsView* m_view;
    SpectrumScene* m_scene;
    QPushButton* m_btn;
    SpectrumPaletteWidget* m_palette;

protected:
    void resizeEvent(QResizeEvent* e) override;

signals:
    void colorChanged(const QColor& color);

public slots:
    void setColor(const QColor& color);
    void updateSpectrum();
};

#endif // COLORSPECTRUMWIDGET_H
