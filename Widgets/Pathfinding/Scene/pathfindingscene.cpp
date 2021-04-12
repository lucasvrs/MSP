#include "pathfindingscene.h"
#include "nodeitem.h"
#include "delimiteritem.h"
#include "Widgets/Pathfinding/Utils/constants.h"
#include "Widgets/Pathfinding/Grid/node.h"
#include "Widgets/Pathfinding/Algorithms/a_star.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

PathfindingScene::PathfindingScene(QObject *parent) :
    QGraphicsScene(parent),
    m_pressed(false),
    m_moved(false),
    m_visitedColor(Qt::green),
    m_startNode(nullptr)
{
}

const QColor& PathfindingScene::visitedColor() const
{
    return m_visitedColor;
}

void PathfindingScene::populateScene()
{
    double x = -(12 * 50 + 25);
    double y = -(12 * 50 + 25);
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            if(i == 0 && j == 0) m_startNode = m_nodes[i][j];
            m_nodes[i][j] = new NodeItem;
            m_nodes[i][j]->setPos(x, y);
            m_nodes[i][j]->node()->setPos({x, y});
            x += 50;
            addItem(m_nodes[i][j]);
        }
        y += 50;
        x = -(12 * 50 + 25);
    }
    m_start = new DelimiterItem(0);
    m_start->setPos(m_nodes[0][0]->pos());
    m_nodes[0][0]->setStart(true);
    m_dest = new DelimiterItem(1);
    m_dest->setInnerColor(Qt::white);
    m_dest->setPos(m_nodes[24][24]->pos());
    m_nodes[24][24]->setDestination(true);
    m_oldStart = m_nodes[0][0];
    m_oldDest = m_nodes[24][24];
    addItem(m_start);
    addItem(m_dest);
    setNodeNeighbors();
}

void PathfindingScene::startIndeces(int &ri, int &rj)
{
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            if(m_nodes[i][j]->pos() == m_start->pos())
            {
                ri = i;
                rj = j;
                return;
            }
        }
    }
}

void PathfindingScene::destIndeces(int &ri, int &rj)
{
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            if(m_nodes[i][j]->pos() == m_dest->pos())
            {
                ri = i;
                rj = j;
                return;
            }
        }
    }
}

const DelimiterItem& PathfindingScene::start() const
{
    return *m_start;
}

const DelimiterItem& PathfindingScene::destination() const
{
    return *m_dest;
}

const NodeItem& PathfindingScene::firstNode() const
{
    return *m_nodes[0][0];
}

//EVENTS**********************************************************
void PathfindingScene::mouseMoveEvent(QGraphicsSceneMouseEvent* e)
{
    if(m_pressed && selectedItems().size() == 1 && m_curMode == 0)
    {
        m_moved = true;
    }
    if(m_pressed && (m_curMode == 1 || m_curMode == 2))
    {
        QGraphicsItem* item = itemAt(e->scenePos(), QTransform());
        if(item != nullptr)
        {
            NodeItem* node = static_cast<NodeItem*>(item);
            if(!node->isObstacle() && m_curMode == 1 && !node->isStart() && !node->isDestination())
            {
                node->setObstacle(true);
                node->setColor(node->obstacleColor());
                node->node()->setVisited(false);
                node->update();
            }
            if(node->isObstacle() && m_curMode == 2 && !node->isStart() && !node->isDestination())
            {
                node->setObstacle(false);
                node->setColor(node->baseColor());
                node->update();
            }
        }
    }
    QGraphicsScene::mouseMoveEvent(e);
}

void PathfindingScene::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    m_pressed = true;
    QGraphicsScene::mousePressEvent(e);
}

//Event fixen
void PathfindingScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
    if(m_pressed && (m_curMode == 1 || m_curMode == 2))
    {
        QGraphicsItem* item = itemAt(e->scenePos(), QTransform());
        if(item != nullptr)
        {
            NodeItem* node = static_cast<NodeItem*>(item);
            if(!node->isObstacle() && m_curMode == 1 && !node->isStart() && !node->isDestination())
            {
                node->setObstacle(true);
                node->node()->setVisited(false);
                node->setColor(node->obstacleColor());
                node->update();
            }
            if(node->isObstacle() && m_curMode == 2 && !node->isStart() && !node->isDestination())
            {
                node->setObstacle(false);
                node->setColor(node->baseColor());
                node->update();
            }
        }
    }
    bool m_isSet = false;
    if(m_moved)
    {
        for(int i = 0; i < 25; i++)
        {
            for(int j = 0; j < 25; j++)
            {
                QRectF bR = m_nodes[i][j]->boundingRect();
                QRectF cR(m_nodes[i][j]->scenePos(), QSizeF(bR.size()));
                if(cR.contains(e->scenePos() + QPointF(25, 25)))
                {
                    if(m_nodes[i][j]->isObstacle() || m_nodes[i][j]->isDestination() || m_nodes[i][j]->isStart())
                    {
                        if(static_cast<DelimiterItem*>(selectedItems()[0])->delimiterType() == Start)
                        {
                            m_start->setPos(m_oldStart->scenePos());
                        }
                        else
                        {
                            m_dest->setPos(m_oldDest->scenePos());
                        }
                        break;
                    }
                    if(static_cast<DelimiterItem*>(selectedItems()[0])->delimiterType() == Start)
                    {
                        m_oldStart->setStart(false);
                        m_start->setPos(m_nodes[i][j]->scenePos());
                        m_nodes[i][j]->setStart(true);
                        m_oldStart = m_nodes[i][j];
                    }
                    else
                    {
                        m_oldDest->setDestination(false);
                        m_dest->setPos(m_nodes[i][j]->scenePos());
                        m_nodes[i][j]->setDestination(true);
                        m_oldDest = m_nodes[i][j];
                    }
                    m_isSet = true;
                    break;
                }
            }
            if(m_isSet) break;
        }
        if(!m_isSet && static_cast<DelimiterItem*>(selectedItems()[0])->delimiterType() == Start) m_start->setPos(m_oldStart->scenePos());
        if(!m_isSet && static_cast<DelimiterItem*>(selectedItems()[0])->delimiterType() == Destination) m_dest->setPos(m_oldDest->scenePos());
    }
    m_moved = false;
    m_pressed = false;
    QGraphicsScene::mouseReleaseEvent(e);
}

//SLOTS*************************************************************************
void PathfindingScene::setMode(int mode)
{
    m_curMode = mode;
    switch(mode)
    {
        case 0:
            m_start->setFlag(QGraphicsItem::ItemIsMovable, true);
            m_start->setFlag(QGraphicsItem::ItemIsSelectable, true);
            m_start->setAcceptHoverEvents(true);
            m_dest->setFlag(QGraphicsItem::ItemIsMovable, true);
            m_dest->setFlag(QGraphicsItem::ItemIsSelectable, true);
            m_dest->setAcceptHoverEvents(true);
            break;
        case 1:
            m_start->setFlag(QGraphicsItem::ItemIsMovable, false);
            m_start->setFlag(QGraphicsItem::ItemIsSelectable, false);
            m_start->setAcceptHoverEvents(false);
            m_dest->setFlag(QGraphicsItem::ItemIsMovable, false);
            m_dest->setFlag(QGraphicsItem::ItemIsSelectable, false);
            m_dest->setAcceptHoverEvents(false);
            break;
        case 2:
            m_start->setFlag(QGraphicsItem::ItemIsMovable, false);
            m_start->setFlag(QGraphicsItem::ItemIsSelectable, false);
            m_start->setAcceptHoverEvents(false);
            m_dest->setFlag(QGraphicsItem::ItemIsMovable, false);
            m_dest->setFlag(QGraphicsItem::ItemIsSelectable, false);
            m_dest->setAcceptHoverEvents(false);
            break;
    }
}

void PathfindingScene::setDelimiterPos(int sCol, int sRow, int dCol, int dRow)
{
    if(!m_nodes[sRow][sCol]->isObstacle())
    {
        m_start->setPos(m_nodes[sRow][sCol]->pos());
        m_oldStart = m_nodes[sRow][sCol];
    }
    if(!m_nodes[dRow][dCol]->isObstacle())
    {
        m_dest->setPos(m_nodes[dRow][dCol]->pos());
        m_oldDest = m_nodes[dRow][dCol];
    }
}

void PathfindingScene::setNodeNeighbors()
{
    bool hasLCol;
    bool hasRCol;
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            hasLCol = false;
            hasRCol = false;
            Node* node = m_nodes[i][j]->node();
            if(j + 1 <= 24)
            {
                node->addNeighbor(m_nodes[i][j + 1]->node());
                hasRCol = true;
            }
            if(j - 1 >= 0)
            {
                node->addNeighbor(m_nodes[i][j - 1]->node());
                hasLCol = true;
            }
            if(i - 1 >= 0)
            {
                if(hasLCol)
                {
                    node->addNeighbor(m_nodes[i - 1][j - 1]->node());
                }
                if(hasRCol)
                {
                    node->addNeighbor(m_nodes[i - 1][j + 1]->node());
                }
                node->addNeighbor(m_nodes[i - 1][j]->node());
            }
            if(i + 1 <= 24)
            {
                if(hasLCol)
                {
                    node->addNeighbor(m_nodes[i + 1][j - 1]->node());
                }
                if(hasRCol)
                {
                    node->addNeighbor(m_nodes[i + 1][j + 1]->node());
                }
                node->addNeighbor(m_nodes[i + 1][j]->node());
            }
        }
    }
}

void PathfindingScene::startScene()
{
    clearVisited();
    QList<Node*> nodes = A_Star::a_star(m_oldStart->node(), m_oldDest->node());
    for(Node* node : nodes)
    {
        for(int i = 0; i < 25; i++)
        {
            for(int j = 0; j < 25; j++)
            {
                NodeItem* item = m_nodes[i][j];
                if(item->node() == node)
                {
                    item->setColor(m_visitedColor);
                    break;
                }
            }
        }
    }
    update();
}

void PathfindingScene::clearVisited()
{
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            NodeItem* item = m_nodes[i][j];
            if(item->node()->visited())
            {
                item->node()->setVisited(false);
                item->setColor(item->baseColor());
            }
        }
    }
}

//SLOTS**************************************************************************
void PathfindingScene::setColor(GuiColorType::Types type, const QColor& color)
{
    switch(type)
    {
        case GuiColorType::StartOut:
            m_start->setColor(color);
            break;
        case GuiColorType::StartIn:
            m_start->setInnerColor(color);
            break;
        case GuiColorType::DestIn:
            m_dest->setInnerColor(color);
            break;
        case GuiColorType::DestOut:
            m_dest->setColor(color);
            break;
        case GuiColorType::Obst:
            clearScene();
            setObstacleColor(color);
            break;
        case GuiColorType::Node:
            clearScene();
            setNodeColor(color);
            break;
        case GuiColorType::Visited:
            clearVisited();
            m_visitedColor = color;
    }
    update();
}

void PathfindingScene::setObstacleColor(const QColor& color)
{
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            m_nodes[i][j]->setObstacleColor(color);
        }
    }
}

void PathfindingScene::setNodeColor(const QColor& color)
{
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            NodeItem* item = m_nodes[i][j];
            item->setBaseColor(color);
            item->setColor(item->baseColor());
        }
    }
}

void PathfindingScene::clearScene()
{
    clearVisited();
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            NodeItem* node = m_nodes[i][j];
            if(node->isObstacle()) node->setObstacle(false);
            node->setColor(node->baseColor());
        }
    }
    update();
}
