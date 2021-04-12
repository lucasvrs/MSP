#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>

/*! Superclass for Pathfinding 2d-Items
 * \brief The GridItem class
 */
class GridItem : public QGraphicsItem
{
public:
    GridItem(int type, QGraphicsItem* parent = nullptr);
    int delimiterType() const;

private:
    int m_type;
};

#endif // GRIDITEM_H
