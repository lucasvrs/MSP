#ifndef RAYTRACINGWIDGET_H
#define RAYTRACINGWIDGET_H

#include <QWidget>

class QGraphicsView;

class RaytracingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RaytracingWidget(QWidget *parent = nullptr);

private:
    QGraphicsView* m_view;

protected:
    void resizeEvent(QResizeEvent* e) override;
};

#endif // RAYTRACINGWIDGET_H
