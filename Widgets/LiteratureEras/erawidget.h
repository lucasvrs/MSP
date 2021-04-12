#ifndef ERAWIDGET_H
#define ERAWIDGET_H

#include <QWidget>

class EpochenScene;
class QSlider;
class EraView;

class EraWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EraWidget(QWidget *parent = nullptr);

private:
    EraView* m_view;
    EpochenScene* m_scene;
    QSlider* m_slider;
    double m_zoom;
    double m_widthMulti;
    double m_sceneHeightAdjust;

protected:
    void resizeEvent(QResizeEvent *e) override;

public slots:
    void adjustSceneRect(double value);
};

#endif // ERAWIDGET_H
