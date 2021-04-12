#include "delimiteritem.h"
#include <QPainter>
#include <QDebug>

DelimiterItem::DelimiterItem(int type, QGraphicsItem *parent) :
    GridItem(type, parent),
    m_color(Qt::red),
    m_innercolor(Qt::red)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void DelimiterItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QBrush(m_color));
    painter->drawEllipse(boundingRect());
    QPen pen(Qt::NoPen);
    painter->setPen(pen);
    painter->setBrush(QBrush(m_innercolor));
    painter->drawEllipse(boundingRect().x() + 5, boundingRect().y() + 5, boundingRect().width() - 10, boundingRect().height() - 10);
}

void DelimiterItem::setColor(const QColor &color)
{
    m_color = color;
}

void DelimiterItem::setInnerColor(const QColor &color)
{
    m_innercolor = color;
}

QRectF DelimiterItem::boundingRect() const
{
    return {-25, -25, 50, 50};
}

const QColor& DelimiterItem::color() const
{
    return m_color;
}

const QColor& DelimiterItem::innerColor() const
{
    return m_innercolor;
}
