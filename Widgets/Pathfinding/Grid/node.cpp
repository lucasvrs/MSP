#include "node.h"
#include <QColor>

Node::Node() :
    m_isDest(false),
    m_isObst(false),
    m_isSource(false),
    m_visited(false)
{

}

/*! Returns all neighbors of the node
 * \brief Node::neighbors
 * \return list of neighbors
 */
const QList<Node*>& Node::neighbors() const
{
    return m_neighbors;
}

const QPointF &Node::pos() const
{
    return m_pos;
}

/*! Adds a neighbor to the node
 * \brief Node::addNeighbor
 * \param node - new neighbor
 */
void Node::addNeighbor(Node* node)
{
    m_neighbors.append(node);
}

bool Node::isDestination() const
{
    return m_isDest;
}

bool Node::isObstacle() const
{
    return m_isObst;
}

bool Node::isSource() const
{
    return m_isSource;
}

bool Node::visited() const
{
    return m_visited;
}

/*! Removes a neighbor
 * \brief Node::removeNeighbor
 * \param node - node to be removed
 */
void Node::removeNeighbor(Node* node)
{
    for(Node* n : m_neighbors)
    {
        if(n == node)
        {
            m_neighbors.removeAll(n);
        }
    }
}

void Node::setAsDestination(bool dest)
{
    if(m_isObst == true || m_isSource == true) return;
    m_isDest = dest;
}

void Node::setAsObstacle(bool obst)
{
    if(m_isDest == true || m_isSource == true) return;
    m_isObst = obst;
}

void Node::setAsSource(bool source)
{
    if(m_isDest == true || m_isObst == true) return;
    m_isSource = source;
}

/*! Sets the type of the nod with the NodeType struct
 * \brief Node::setNodeType
 * \param type - NodeType
 */
void Node::setNodeType(NodeType::NodeTypes type)
{
    switch(type)
    {
    case NodeType::None:
        m_isDest = false;
        m_isObst = false;
        m_isSource = false;
        break;
    case NodeType::Destination:
        m_isDest = true;
        m_isObst = false;
        m_isSource = false;
        break;
    case NodeType::Obstacle:
        m_isDest = false;
        m_isObst = true;
        m_isSource = false;
        break;
    case NodeType::Source:
        m_isDest = false;
        m_isObst = false;
        m_isSource = true;
        break;
    }
}

void Node::setPos(const QPointF& pos)
{
    m_pos = pos;
}

void Node::setVisited(bool visit)
{
    m_visited = visit;
}
