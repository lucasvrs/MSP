#include "pathfindingoptionswidget.h"
#include "pathfindinglogicoptionswidget.h"

PathfindingOptionsWidget::PathfindingOptionsWidget(QWidget *parent) :
    QTabWidget(parent)
{
    m_guiOptions = new PathfindingGuiOptionsWidget;
    m_logicOptions = new PathfindingLogicOptionsWidget;
    addTab(m_guiOptions, "Interface");
    addTab(m_logicOptions, "Logic");
    connect(m_guiOptions, &PathfindingGuiOptionsWidget::closeOptions, this, &PathfindingOptionsWidget::closeOptions);
    connect(m_logicOptions, &PathfindingLogicOptionsWidget::closeOptions, this, &PathfindingOptionsWidget::closeOptions);
    connect(m_logicOptions, &PathfindingLogicOptionsWidget::delimiterPosChanged, this, &PathfindingOptionsWidget::delimiterPosChanged);
    connect(m_guiOptions, &PathfindingGuiOptionsWidget::colorChanged, this, &PathfindingOptionsWidget::colorChanged);
}

void PathfindingOptionsWidget::setDestRow(int i)
{
    m_logicOptions->setDestRow(i);
}

void PathfindingOptionsWidget::setStartRow(int i)
{
    m_logicOptions->setStartRow(i);
}

void PathfindingOptionsWidget::setDestCol(int i)
{
    m_logicOptions->setDestCol(i);
}

void PathfindingOptionsWidget::setStartCol(int i)
{
    m_logicOptions->setStartCol(i);
}

void PathfindingOptionsWidget::setStartOutColor(const QColor& color)
{
    m_guiOptions->setBtnColor(GuiColorType::StartOut, color);
}

void PathfindingOptionsWidget::setStartInColor(const QColor& color)
{
    m_guiOptions->setBtnColor(GuiColorType::StartIn, color);
}

void PathfindingOptionsWidget::setDestOutColor(const QColor& color)
{
    m_guiOptions->setBtnColor(GuiColorType::DestOut, color);
}

void PathfindingOptionsWidget::setDestInColor(const QColor& color)
{
    m_guiOptions->setBtnColor(GuiColorType::DestIn, color);
}

void PathfindingOptionsWidget::setObstColor(const QColor& color)
{
    m_guiOptions->setBtnColor(GuiColorType::Obst, color);
}

void PathfindingOptionsWidget::setNodeColor(const QColor& color)
{
    m_guiOptions->setBtnColor(GuiColorType::Node, color);
}

void PathfindingOptionsWidget::setVisitedColor(const QColor& color)
{
    m_guiOptions->setBtnColor(GuiColorType::Visited, color);
}


