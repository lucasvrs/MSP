#ifndef PATHFINDINGOPTIONSWIDGET_H
#define PATHFINDINGOPTIONSWIDGET_H

#include <QTabWidget>
#include "pathfindingguiwidget.h"

class PathfindingGuiOptionsWidget;
class PathfindingLogicOptionsWidget;

class PathfindingOptionsWidget : public QTabWidget
{
    Q_OBJECT

public:
    PathfindingOptionsWidget(QWidget* parent = nullptr);

private:
    PathfindingGuiOptionsWidget* m_guiOptions;
    PathfindingLogicOptionsWidget* m_logicOptions;

signals:
    void closeOptions();
    void delimiterPosChanged(int sCol, int sRow, int dCol, int dRow);
    void colorChanged(GuiColorType::Types type, const QColor& color);

public slots:
    void setDestRow(int i);
    void setStartRow(int i);
    void setDestCol(int i);
    void setStartCol(int i);
    void setStartOutColor(const QColor& color);
    void setStartInColor(const QColor& color);
    void setDestOutColor(const QColor& color);
    void setDestInColor(const QColor& color);
    void setObstColor(const QColor& color);
    void setNodeColor(const QColor& color);
    void setVisitedColor(const QColor& color);
};

#endif // PATHFINDINGOPTIONSWIDGET_H
