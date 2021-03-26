#ifndef ADDTILE_H
#define ADDTILE_H

#include "tileitem.h"

class AddTile : public TileItem
{
public:
    AddTile(QGraphicsItem* parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e) override;
};

#endif // ADDTILE_H
