#include "a_star.h"
#include "Widgets/Pathfinding/Grid/node.h"
#include "Widgets/Pathfinding/Utils/utils.h"
#include "Widgets/Pathfinding/Utils/constants.h"

/*! Calculates heuristic
 * \brief A_Star::calcH
 * \param n     - Currently screened node
 * \param dest  - Destination node
 * \return float number
 */
float A_Star::calcH(const Node& n, const Node& dest)
{
    return sqrt((2*abs(n.pos().x()-dest.pos().x()))+(2*abs(n.pos().y()-dest.pos().y())));
}

/*! Calculates weight of the path between node a and node b
 * \brief A_Star::calcG
 * \param a - Source node
 * \param b - Destination node
 * \return float number
 */
float A_Star::calcG(const Node& a, const Node& b)
{
    return distance(a.pos(), b.pos());
}

/*! Calculates the value of the addition of weigh and heuristic
 * \brief A_Star::calcF
 * \param a - Source node
 * \param b - Destination node
 * \param dest - Destination node of graph
 * \return float number
 */
float A_Star::calcF(const Node& a, const Node& b, const Node& dest)
{
    return calcG(a, b) + calcH(b, dest);
}

/*! Returns the nodes of the path taken
 * \brief A_Star::a_star
 * \param start - Start node
 * \param dest  - Destination node
 * \return list of nodes
 */
QList<Node*> A_Star::a_star(Node* start, Node* dest)
{
    start->setVisited(true);
    QList<Node*> visited;
    int steps = 0;
    Node* cur;
    Node* last;
    cur = last = start;
    do
    {
        Node* next = nextNode(cur, dest);
        if(next != nullptr)
        {
            last = cur;
            cur = next;
            cur->setVisited(true);
            if(!cur->isDestination()) visited.push_back(cur);
        }
        else
        {
            cur->setVisited(true);
            cur = last;
            if(!visited.isEmpty())
            {
                visited.pop_back();
                (visited.size() > 1) ? last = visited.last() : last = start;
            }
        }
        steps++;
    } while(!cur->isDestination() && steps < MAX_STEPS);
    return visited;
}

/*! Returns the node which is nearest to the destination node
 * \brief A_Star::nextNode
 * \param node - Current node
 * \param dest - Destination node
 * \return next node to use
 */
Node* A_Star::nextNode(Node* node, Node* dest)
{
    Node* nextNode = nullptr;
    float fa = -99.0;
    bool first = true;
    for(Node* n : node->neighbors())
    {
        if(!n->visited() && !n->isObstacle())
        {
            float fb = calcF(*node, *n, *dest);
            if(fa > fb || first)
            {
                nextNode = n;
                fa = fb;
                first = false;
            }
        }
    }
    return nextNode;
}
