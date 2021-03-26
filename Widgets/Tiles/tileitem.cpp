#include "tileitem.h"
#include <QPainter>

TileItem::TileItem(QGraphicsItem* parent) : QGraphicsItem(parent), m_height(100), m_width(100)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void TileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen(Qt::SolidLine);
    pen.setWidth(3);
    painter->setRenderHint(QPainter::Antialiasing, true);
    (isSelected()) ? pen.setColor(Qt::blue) : pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->setBrush(m_color);
    painter->drawRoundedRect(boundingRect(), 5, 5);
    QFont f("Helvetica");
    painter->setFont(f);
    QFontMetrics m(f);
    pen.setColor(m_textColor);
    painter->setPen(pen);
    if(!m_text.isEmpty()) painter->drawText(QPointF(-m.width(m_text)/3, 0), m_text);
}

QRectF TileItem::boundingRect() const
{
    return {-m_width / 2, -m_height / 2, m_width, m_height};
}

void TileItem::setColor(const QColor& c)
{
    m_color = c;
}

void TileItem::setTextColor(const QColor& c)
{
    m_textColor = c;
}

void TileItem::setHeight(double h)
{
    m_height = h;
}

void TileItem::setWidth(double w)
{
    m_width = w;
}

void TileItem::setText(const QString &text)
{
    m_text = text;
}

void TileItem::setWidget(QWidget *widget)
{
    m_widget = widget;
}

double TileItem::height() const
{
    return m_height;
}

double TileItem::width() const
{
    return m_width;
}

const QString& TileItem::text() const
{
    return m_text;
}

QWidget* TileItem::widget() const
{
    return m_widget;
}
