#ifndef PATHFINDINGSCENE_H
#define PATHFINDINGSCENE_H

#include <QGraphicsScene>
#include "Widgets/Pathfinding/pathfindingguiwidget.h"

class DelimiterItem;
class NodeItem;

class PathfindingScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PathfindingScene(QObject *parent = nullptr);
    const QColor& visitedColor() const;
    void populateScene();
    void startIndeces(int& ri, int& rj);
    void destIndeces(int& ri, int& rj);
    const DelimiterItem& start() const;
    const DelimiterItem& destination() const;
    const NodeItem& firstNode() const;

private:
    bool m_pressed;
    bool m_moved;
    QColor m_visitedColor;
    DelimiterItem* m_start;
    DelimiterItem* m_dest;
    NodeItem* m_nodes[25][25];
    NodeItem* m_oldStart;
    NodeItem* m_startNode;
    NodeItem* m_oldDest;
    NodeItem* m_destNode;
    int m_curMode;
    void setNodeNeighbors();
    void clearVisited();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* e);
    void mousePressEvent(QGraphicsSceneMouseEvent* e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);

private slots:
    void setObstacleColor(const QColor& color);
    void setNodeColor(const QColor& color);

public slots:
    void setMode(int mode);
    void setDelimiterPos(int sCol, int sRow, int dCol, int dRow);
    void setColor(GuiColorType::Types type, const QColor& color);
    void startScene();
    void clearScene();
};

#endif // PATHFINDINGSCENE_H
