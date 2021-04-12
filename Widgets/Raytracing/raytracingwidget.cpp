#include "raytracingwidget.h"
#include "raytracingscene.h"
#include <QGraphicsView>
#include <QGridLayout>
#include <QScrollBar>

RaytracingWidget::RaytracingWidget(QWidget *parent) : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(this);
    RaytracingScene* scene = new RaytracingScene;
    scene->setSceneRect(-1500, -1000, 3000, 2000);
    m_view = new QGraphicsView;
    m_view->setScene(scene);
    m_view->horizontalScrollBar()->setDisabled(true);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->verticalScrollBar()->setDisabled(true);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout->addWidget(m_view);
    scene->startTracing();
    m_view->centerOn(0, 0);
    m_view->scale(0.8, 0.8);
}

//EVENTS******************************************************************
void RaytracingWidget::resizeEvent(QResizeEvent* e)
{
    m_view->centerOn(0, 0);
    QWidget::resizeEvent(e);
}
