#ifndef A_STAR_H
#define A_STAR_H

#include <QList>

class Node;

/*! Node on path
 * \brief The PathNode struct
 */
struct PathNode
{
    enum Type
    {
        OnPath = 0,
        OnlyVisited
    };
    Node* node;
    Type type;
};

/*! Class holding methods for the a* algorithm
 * \brief The A_Star class
 */
class A_Star
{
public:
    A_Star() = default;
    static QList<Node *> a_star(Node *start, Node *dest);

private:
    static float calcH(const Node& n, const Node &dest);
    static float calcG(const Node& a, const Node& b);
    static float calcF(const Node& a, const Node& b, const Node &dest);
    static Node* nextNode(Node* node, Node* dest);
};

#endif // A_STAR_H
