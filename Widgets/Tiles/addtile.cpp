/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "addtile.h"
#include <QPainter>
#include <QDebug>

AddTile::AddTile(QGraphicsItem *parent) : TileItem(parent)
{
    setText("+");
}

void AddTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen(Qt::SolidLine);
    pen.setWidth(3);
    painter->setRenderHint(QPainter::Antialiasing, true);
    (isSelected()) ? pen.setColor(Qt::blue) : pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->setBrush(Qt::white);
    painter->drawRoundedRect(boundingRect(), 5, 5);
    QFont f("Helvetica");
    painter->setFont(f);
    QFontMetrics m(f);
    painter->drawText(QPointF(-m.width(text())/3, 0), text());
}

//EVENTS*******************************************************
void AddTile::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
    QGraphicsItem::mouseReleaseEvent(e);
}
