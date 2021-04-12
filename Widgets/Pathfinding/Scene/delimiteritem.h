#ifndef DELIMITERITEM_H
#define DELIMITERITEM_H

#include "griditem.h"

class DelimiterItem : public GridItem
{
public:
    DelimiterItem(int type, QGraphicsItem* parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    void setColor(const QColor& color);
    void setInnerColor(const QColor& color);
    QRectF boundingRect() const override;
    const QColor& color() const;
    const QColor& innerColor() const;

private:
    QColor m_color;
    QColor m_innercolor;
};

#endif // DELIMITERITEM_H
