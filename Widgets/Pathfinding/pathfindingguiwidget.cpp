#include "pathfindingguiwidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QColorDialog>
#include <QDebug>

PathfindingGuiOptionsWidget::PathfindingGuiOptionsWidget(QWidget *parent) : QWidget(parent), m_changes(false)
{
    QGridLayout* layout = new QGridLayout(this);
    QLabel* startNodeLabel = new QLabel("Start-Node:");
    QLabel* startOutColLabel = new QLabel("Outer color:");
    QLabel* startInColLabel = new QLabel("Inner color:");
    QLabel* destNodeLabel = new QLabel("Destination-Node:");
    QLabel* destOutColLabel = new QLabel("Outer color:");
    QLabel* destInColLabel = new QLabel("Inner color:");
    QLabel* obstNodeLabel = new QLabel("Obstacle-Node:");
    QLabel* obstColLabel = new QLabel("Color:");
    QLabel* nodeLabel = new QLabel("Node:");
    QLabel* nodeColLabel = new QLabel("Color:");
    QLabel* visitedLabel = new QLabel("Visited:");
    QLabel* visitedColLabel = new QLabel("Color:");
    m_startOutColBtn = new QPushButton;
    m_startInColBtn = new QPushButton;
    m_destOutColBtn = new QPushButton;
    m_destInColBtn = new QPushButton;
    m_obstColBtn = new QPushButton;
    m_nodeColBtn = new QPushButton;
    m_visitedColBtn = new QPushButton;
    m_btns.append(m_startOutColBtn);
    m_btns.append(m_startInColBtn);
    m_btns.append(m_destOutColBtn);
    m_btns.append(m_destInColBtn);
    m_btns.append(m_obstColBtn);
    m_btns.append(m_nodeColBtn);
    m_btns.append(m_visitedColBtn);
    m_btnTypeMap.insert(std::pair<QPushButton*, GuiColorType::Types>(m_startOutColBtn, GuiColorType::StartOut));
    m_btnTypeMap.insert(std::pair<QPushButton*, GuiColorType::Types>(m_startInColBtn, GuiColorType::StartIn));
    m_btnTypeMap.insert(std::pair<QPushButton*, GuiColorType::Types>(m_destInColBtn, GuiColorType::DestIn));
    m_btnTypeMap.insert(std::pair<QPushButton*, GuiColorType::Types>(m_destOutColBtn, GuiColorType::DestOut));
    m_btnTypeMap.insert(std::pair<QPushButton*, GuiColorType::Types>(m_obstColBtn, GuiColorType::Obst));
    m_btnTypeMap.insert(std::pair<QPushButton*, GuiColorType::Types>(m_nodeColBtn, GuiColorType::Node));
    m_btnTypeMap.insert(std::pair<QPushButton*, GuiColorType::Types>(m_visitedColBtn, GuiColorType::Visited));
    QPushButton* cancelBtn = new QPushButton("Cancel");
    QPushButton* applyBtn = new QPushButton("Apply");
    QPushButton* saveBtn = new QPushButton("Save");
    QSpacerItem* hSpacer = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* vSpacer = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addWidget(startNodeLabel, 0, 0);
    layout->addWidget(startOutColLabel, 1, 0);
    layout->addWidget(m_startOutColBtn, 1, 1);
    layout->addWidget(startInColLabel, 2, 0);
    layout->addWidget(m_startInColBtn, 2, 1);

    layout->addWidget(destNodeLabel, 0, 2);
    layout->addWidget(destOutColLabel, 1, 2);
    layout->addWidget(m_destOutColBtn, 1, 3);
    layout->addWidget(destInColLabel, 2, 2);
    layout->addWidget(m_destInColBtn, 2, 3);

    layout->addItem(hSpacer, 1, 4);

    layout->addWidget(obstNodeLabel, 3, 0);
    layout->addWidget(obstColLabel, 4, 0);
    layout->addWidget(m_obstColBtn, 4, 1);

    layout->addWidget(nodeLabel, 3, 2);
    layout->addWidget(nodeColLabel, 4, 2);
    layout->addWidget(m_nodeColBtn, 4, 3);

    layout->addWidget(visitedLabel, 5, 0);
    layout->addWidget(visitedColLabel, 6, 0);
    layout->addWidget(m_visitedColBtn, 6, 1);

    layout->addItem(vSpacer, 7, 0);

    layout->addWidget(cancelBtn, 8, 5);
    layout->addWidget(applyBtn, 8, 6);
    layout->addWidget(saveBtn, 8, 7);

    connect(cancelBtn, &QPushButton::clicked, [this]()
    {
        m_changes = false;
        closeOptions();
    });
    connect(applyBtn, &QPushButton::clicked, [this]()
    {
        m_changes = true;
    });
    connect(saveBtn, &QPushButton::clicked, [this]()
    {
        if(m_changes) applyChanges();
        m_changes = false;
        closeOptions();
    });
    for(QPushButton* btn : m_btns)
    {
        connect(btn, &QPushButton::clicked, [this, btn]()
        {
            openColorPicker(btn);
        });
    }
}

void PathfindingGuiOptionsWidget::openColorPicker(QPushButton* btn)
{
    QColor c = QColorDialog::getColor();
    setBtnColor(btn, c);
}

void PathfindingGuiOptionsWidget::setBtnColor(QPushButton* btn, const QColor& color)
{
    btn->setStyleSheet(
                "QPushButton{ background-color: rgba(" + QString::number(color.red()) +
                "," + QString::number(color.green()) + ", " + QString::number(color.blue()) +
                "," + QString::number(color.alpha()) + ");}"
                );
}

void PathfindingGuiOptionsWidget::setBtnColor(GuiColorType::Types type, const QColor& color)
{
    for(auto itr : m_btnTypeMap)
    {
        if(itr.second == type)
        {
            itr.first->setStyleSheet(
                        "QPushButton{ background-color: rgba(" + QString::number(color.red()) +
                        "," + QString::number(color.green()) + ", " + QString::number(color.blue()) +
                        "," + QString::number(color.alpha()) + ");}"
                        );
            return;
        }
    }
}

void PathfindingGuiOptionsWidget::applyChanges()
{
    for(auto itr = m_btnTypeMap.begin(); itr != m_btnTypeMap.end(); itr++)
    {
        emit colorChanged(itr->second, itr->first->palette().color(QPalette::ColorRole::Background));
    }
}
