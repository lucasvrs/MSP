#ifndef RAYTRACINGSCENE_H
#define RAYTRACINGSCENE_H

#include <QGraphicsScene>
#include "Utils/shapes2d.h"

class RaytracingScene : public QGraphicsScene
{
public:
    RaytracingScene(QObject* parent = nullptr);
    void startTracing();
    void drawRays();
    void deleteItems();
    bool bulbInItem();

private:
    QGraphicsEllipseItem* m_bulb;
    QList<LineSegment> m_boundaries;
    QList<Circle> m_circles;
    QList<QGraphicsItem*> m_obstacles;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* e) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* e) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e) override;
};

#endif // RAYTRACINGSCENE_H
