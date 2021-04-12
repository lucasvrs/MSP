#ifndef NODEITEM_H
#define NODEITEM_H

#include "griditem.h"

class Node;

class NodeItem : public GridItem
{
public:
    NodeItem(int type = 3, QGraphicsItem* parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    void setColor(const QColor& color);
    void setObstacleColor(const QColor& color);
    void setBaseColor(const QColor& color);
    void setStart(bool isStart);
    void setDestination(bool isDest);
    void setObstacle(bool isObst);
    QRectF boundingRect() const override;
    const QColor& color() const;
    const QColor& obstacleColor() const;
    const QColor& baseColor() const;
    bool isStart() const;
    bool isDestination() const;
    bool isObstacle() const;
    Node* node() const;

private:
    Node* m_node;
    QColor m_color;
    QColor m_obstColor;
    QColor m_baseColor;
    bool m_isStart;
    bool m_isDest;
    bool m_isObst;
};

#endif // NODEITEM_H
