#include "nodeitem.h"
#include "Widgets/Pathfinding/Grid/node.h"
#include <QPainter>
#include <QDebug>

NodeItem::NodeItem(int type, QGraphicsItem* parent) :
    GridItem(type, parent),
    m_color(Qt::white),
    m_baseColor(Qt::white),
    m_isStart(false),
    m_isDest(false),
    m_isObst(false)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    m_node = new Node();
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QBrush(m_color));
    painter->drawRect(boundingRect());
}

void NodeItem::setBaseColor(const QColor& color)
{
    m_baseColor = color;
}

void NodeItem::setColor(const QColor &color)
{
    m_color = color;
}

void NodeItem::setObstacleColor(const QColor &color)
{
    m_obstColor = color;
}

void NodeItem::setStart(bool isStart)
{
    m_node->setAsSource(isStart);
    m_isStart = isStart;
}
void NodeItem::setDestination(bool isDest)
{
    m_node->setAsDestination(isDest);
    m_isDest = isDest;
}

void NodeItem::setObstacle(bool isObst)
{
    if(m_isStart || m_isDest) return;
    m_node->setAsObstacle(isObst);
    m_isObst = isObst;
}

QRectF NodeItem::boundingRect() const
{
    return {-25, -25, 50, 50};
}

const QColor& NodeItem::color() const
{
    return m_color;
}

const QColor& NodeItem::obstacleColor() const
{
    return m_obstColor;
}

const QColor& NodeItem::baseColor() const
{
    return m_baseColor;
}

bool NodeItem::isStart() const
{
    return m_isStart;
}

bool NodeItem::isDestination() const
{
    return m_isDest;
}

bool NodeItem::isObstacle() const
{
    return m_isObst;
}

Node* NodeItem::node() const
{
    return m_node;
}
