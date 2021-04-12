#ifndef HANDLEITEM_H
#define HANDLEITEM_H

#include <QGraphicsItem>

class HandleItem : public QGraphicsItem
{
public:
    HandleItem(QGraphicsItem* parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const override;
    QColor getColor(int w);
};

#endif // HANDLEITEM_H
