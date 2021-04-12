#include "erabutton.h"
#include <QPainter>
#include <QDebug>

EraButton::EraButton(const QString &title, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_title(title),
    m_x(0), m_y(0),
    m_width(100), m_height(100)
{
    this->setAcceptHoverEvents(true);
}

void EraButton::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QFontMetrics fm(m_font);
    QPainterPath path;
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setBrush(QBrush(m_color));
    path.addRoundedRect(boundingRect(), 5, 5);
    painter->drawPath(path);
    QPainterPath path2;
    painter->setBrush(QBrush(Qt::black));
    path2.addText(m_x - fm.width(m_title) / 2 + m_width / 2, m_y + fm.height() / 3 + m_height / 2, m_font, m_title);
    painter->drawPath(path2);
}

void EraButton::setColor(const QColor &color)
{
    m_color = color;
}

void EraButton::setGeometry(double x, double y, double width, double height)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
}

void EraButton::setFont(const QFont &font)
{
    m_font = font;
}

QRectF EraButton::boundingRect() const
{
    return QRectF(m_x, m_y, m_width, m_height);
}

void EraButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsItem::mouseReleaseEvent(e);
}

void EraButton::hoverEnterEvent(QGraphicsSceneHoverEvent *e)
{
    setOpacity(0.7);
    QGraphicsItem::hoverEnterEvent(e);
}

void EraButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *e)
{
    setOpacity(1.0);
    QGraphicsItem::hoverLeaveEvent(e);
}
