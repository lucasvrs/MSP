#include "pathfindingwidget.h"
#include "Scene/view.h"
#include "Scene/pathfindingscene.h"
#include "Utils/constants.h"
#include "pathfindingoptionswidget.h"
#include "Scene/delimiteritem.h"
#include "Scene/nodeitem.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QKeyEvent>
#include <QDebug>
#include <QPushButton>

PathfindingWidget::PathfindingWidget(QWidget *parent) : QWidget(parent), m_options(nullptr)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QHBoxLayout* hlayout = new QHBoxLayout;
    m_modeBox = new QComboBox;
    for(const char* item : MODE_STRINGLIST)
    {
        m_modeBox->addItem(item);
    }
    View* view = new View;
    QPushButton* startBtn = new QPushButton("Start");
    QPushButton* clearAllBtn = new QPushButton("Clear");
    QPushButton* optionsBtn = new QPushButton("Options");
    QPushButton* helpBtn = new QPushButton("Help");
    m_scene = new PathfindingScene;
    m_scene->populateScene();
    view->setScene(m_scene);
    hlayout->addWidget(startBtn);
    hlayout->addWidget(m_modeBox);
    hlayout->addWidget(clearAllBtn);
    hlayout->addWidget(optionsBtn);
    hlayout->addWidget(helpBtn);
    layout->addLayout(hlayout);
    layout->addWidget(view);
    view->scale(0.7, 0.7);

    connect(m_modeBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int i)
    {
        setMode(m_modeList[i]);
        m_scene->setMode(i);
    });
    connect(optionsBtn, &QPushButton::clicked, this, &PathfindingWidget::openOptions);
    connect(startBtn, &QPushButton::clicked, m_scene, &PathfindingScene::startScene);
    connect(clearAllBtn, &QPushButton::clicked, m_scene, &PathfindingScene::clearScene);
    connect(m_scene, &PathfindingScene::sceneRectChanged, [this, view]()
    {
        m_scene->setSceneRect(-1025, -625, 2000, 1200);
        view->centerOn(0, 0);
    });

    m_modeBox->setCurrentIndex(1);
    m_modeBox->setCurrentIndex(0);
}

void PathfindingWidget::setMode(Pathfinding::Modes mode)
{
    m_curMode = mode;
}

Pathfinding::Modes PathfindingWidget::mode() const
{
    return m_curMode;
}

//EVENTS*********************************************************************
void PathfindingWidget::keyReleaseEvent(QKeyEvent* e)
{
    //Shortcuts
    if(e->key() == Qt::Key_Escape)
    {
        openOptions();
    }
    if(e->modifiers() == Qt::ControlModifier)
    {
        if(e->key() == Qt::Key_1) m_modeBox->setCurrentIndex(0);
        if(e->key() == Qt::Key_2) m_modeBox->setCurrentIndex(1);
        if(e->key() == Qt::Key_3) m_modeBox->setCurrentIndex(2);
        if(e->key() == Qt::Key_D) m_scene->clearScene();
        if(e->key() == Qt::Key_R) m_scene->startScene();
    }
    QWidget::keyReleaseEvent(e);
}

void PathfindingWidget::resizeEvent(QResizeEvent* e)
{
    QWidget::resizeEvent(e);
    if(m_options != nullptr) m_options->setGeometry(geometry());
}

//SLOTS******************************************************************
void PathfindingWidget::openOptions()
{
    if(m_options == nullptr)
    {
        m_options = new PathfindingOptionsWidget(this);
        int dC, dR, sC, sR;
        m_scene->startIndeces(sC, sR);
        m_scene->destIndeces(dC, dR);
        m_options->setDestCol(dC + 1);
        m_options->setDestRow(dR + 1);
        m_options->setStartCol(sC + 1);
        m_options->setStartRow(sR + 1);
        m_options->setDestInColor(m_scene->destination().innerColor());
        m_options->setDestOutColor(m_scene->destination().color());
        m_options->setStartOutColor(m_scene->start().color());
        m_options->setStartInColor(m_scene->start().innerColor());
        m_options->setNodeColor(m_scene->firstNode().baseColor());
        m_options->setObstColor(m_scene->firstNode().obstacleColor());
        m_options->setVisitedColor(m_scene->visitedColor());
        m_options->setGeometry(geometry());
        m_options->show();
        connect(m_options, &PathfindingOptionsWidget::closeOptions, [this]
        {
            delete m_options;
            m_options = nullptr;
        });
        connect(m_options, &PathfindingOptionsWidget::delimiterPosChanged,
                m_scene, &PathfindingScene::setDelimiterPos);
        connect(m_options, &PathfindingOptionsWidget::colorChanged, m_scene, &PathfindingScene::setColor);
    }
    else
    {
        delete m_options;
        m_options = nullptr;
    }
}
