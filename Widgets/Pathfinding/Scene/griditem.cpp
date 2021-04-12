#include "griditem.h"

GridItem::GridItem(int type, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_type(type)
{

}

int GridItem::delimiterType() const
{
    return m_type;
}
