#ifndef NODE_H
#define NODE_H

#include <QList>

class QColor;

/*! Describes wether the node is a normal node, the destination node, the source node or an obstacle node
 * \brief The NodeType struct
 */
struct NodeType
{
    enum NodeTypes
    {
        None = 0,
        Destination,
        Obstacle,
        Source
    };
};

class Node
{
public:
    Node();
    const QList<Node*>& neighbors() const;
    const QPointF& pos() const;
    void addNeighbor(Node *node);
    bool isDestination() const;
    bool isObstacle() const;
    bool isSource() const;
    bool visited() const;
    void removeNeighbor(Node *node);
    void setAsDestination(bool dest);
    void setAsObstacle(bool obst);
    void setAsSource(bool source);
    void setNodeType(NodeType::NodeTypes type);
    void setPos(const QPointF& pos);
    void setVisited(bool visit);

private:
    bool m_isDest;
    bool m_isObst;
    bool m_isSource;
    bool m_visited;
    QColor* m_color;
    QList<Node*> m_neighbors;
    QPointF m_pos;
};

#endif // NODE_H
