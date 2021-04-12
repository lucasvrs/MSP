#include "raytracingscene.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QDebug>
#include "Utils/utils.h"
#include "Utils/geometrylib.h"

RaytracingScene::RaytracingScene(QObject *parent) : QGraphicsScene(parent)
{
    m_bulb = new QGraphicsEllipseItem(QRectF(-25, -25, 50, 50));
    m_bulb->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable, true);
    m_bulb->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable, true);
    m_bulb->setZValue(2);
    m_bulb->setBrush(QBrush(Qt::yellow));
    addItem(m_bulb);
}

bool RaytracingScene::bulbInItem()
{
    for(QGraphicsItem* item : m_obstacles)
    {
        if(item == m_bulb) continue;
        if(item->contains(m_bulb->scenePos())) return true;
    }
    return false;
}

void RaytracingScene::startTracing()
{
    m_boundaries = {
        LineSegment(p2v(sceneRect().topRight()), p2v(sceneRect().bottomRight())),
        LineSegment(p2v(sceneRect().bottomRight()), p2v(sceneRect().bottomLeft())),
        LineSegment(p2v(sceneRect().bottomLeft()), p2v(sceneRect().topLeft())),
        LineSegment(p2v(sceneRect().topLeft()), p2v(sceneRect().topRight())),
        LineSegment(Vec(0, -550), Vec(550, 0)),
        LineSegment(Vec(0, -350), Vec(-350, 0))
    };
    m_circles = {
        Circle(Vec(-100, -100), 50),
        Circle(Vec(-200, 400), 80)
    };
    drawRays();
}

void RaytracingScene::drawRays()
{
    deleteItems();
    for(LineSegment seg : m_boundaries)
    {
        QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(v2p(seg.p0), v2p(seg.p1)));
        m_obstacles.push_back(line);
        addItem(line);
    }
    for(Circle circle : m_circles)
    {
        QGraphicsEllipseItem* e = new QGraphicsEllipseItem(QRectF(v2p(circle.p) - QPointF(circle.r, circle.r),
                                                                  QSizeF(circle.r * 2, circle.r * 2)));
        m_obstacles.push_back(e);
        addItem(e);
    }
    if(bulbInItem()) return;
    Vec ip;
    Vec resIp;
    bool isSet;
    QPointF pos = m_bulb->pos();
    Vec c(pos.x(), pos.y());
    for(int i = 0; i < 360; i+=5)
    {
        isSet = false;
        for(LineSegment seg : m_boundaries)
        {
            if(hasLineLineIntersection(LineSegment(c, c + Vec(2, 0).rotated(i)), seg, ip))
            {
                if(!isSet)
                {
                    resIp = ip;
                    isSet = true;
                    continue;
                }
                resIp = nearestPoint(c, resIp, ip);
            }
        }
        for(Circle circle : m_circles)
        {
            if(hasLineCircleIntersection(LineSegment(c, c + Vec(2, 0).rotated(i)), circle, ip))
            {
                if(!isSet)
                {
                    resIp = ip;
                    isSet = true;
                    continue;
                }
                resIp = nearestPoint(c, resIp, ip);
            }
        }
        if(isSet)
        {
            QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(v2p(c), v2p(resIp)));
            line->setPen(QPen(Qt::darkYellow));
            addItem(line);
        }
    }
    update();
}

void RaytracingScene::deleteItems()
{
    for(QGraphicsItem* item : items())
    {
        if(item == m_bulb) continue;
        removeItem(item);
    }
    m_obstacles.clear();
}

//EVENTS***************************************************************************************************
void RaytracingScene::mouseMoveEvent(QGraphicsSceneMouseEvent* e)
{
    if(selectedItems().size() == 1)
    {
        drawRays();
    }
    QGraphicsScene::mouseMoveEvent(e);
}

void RaytracingScene::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    QGraphicsScene::mousePressEvent(e);
}

void RaytracingScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
    QGraphicsScene::mouseReleaseEvent(e);
}
