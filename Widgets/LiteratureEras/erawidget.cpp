#include "erawidget.h"
#include "epochenscene.h"
#include "constants.h"
#include "eraview.h"
#include <QGridLayout>
#include <QSlider>
#include <QDebug>
#include <QGraphicsItem>
#include <QPushButton>
#include <QSpacerItem>

EraWidget::EraWidget(QWidget *parent) :
    QWidget(parent),
    m_zoom(100),
    m_widthMulti(1.0),
    m_sceneHeightAdjust(100)
{
    QGridLayout* mainLayout = new QGridLayout(this);
    m_view = new EraView();
    mainLayout->addWidget(m_view);
    m_scene = new EpochenScene();
    m_scene->populateScene();
    m_view->setScene(m_scene);

    m_scene->setSceneRect(-(TIMELINE_BORDER * DIVISOR + 50), -(m_view->height() - m_sceneHeightAdjust) / 2,
                          (2 * TIMELINE_BORDER * DIVISOR + 100), m_view->height() - m_sceneHeightAdjust);

    QGridLayout* layout = new QGridLayout(m_view);
    QSpacerItem* hSpace = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* vSpace = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QPushButton* zoomOutBtn = new QPushButton("-");
    zoomOutBtn->setFixedSize(50, 50);
    QPushButton* zoomInBtn = new QPushButton("+");
    zoomInBtn->setFixedSize(50, 50);
    m_slider = new QSlider(Qt::Orientation::Horizontal);
    m_slider->setMinimum(-1);
    m_slider->setMaximum(4);
    m_slider->setFixedWidth(200);
    layout->addItem(hSpace, 0, 0, 1, 1);
    layout->addItem(vSpace, 1, 2, 1, 1);
    layout->addWidget(m_slider, 0, 1, 1, 1);
    layout->addWidget(zoomOutBtn, 0, 2, 1, 1);
    layout->addWidget(zoomInBtn, 0, 3, 1, 1);

    connect(zoomOutBtn, &QPushButton::clicked, [this]()
    {
        if(m_zoom > 50)
        {
            m_view->scale(0.8, 0.8);
            m_zoom *= 0.8;
        }
    });
    connect(zoomInBtn, &QPushButton::clicked, [this]()
    {
        if(m_zoom < 150)
        {
            m_view->scale(1.25, 1.25);
            m_zoom *= 1.25;
        }
    });
    connect(m_slider, &QSlider::valueChanged, [this](int value)
    {
        double dValue = value;
        if(value >= 0)
        {
            adjustSceneRect(dValue + 1.0);
        }
        else
        {
            adjustSceneRect(1.0 / (dValue * -1.0 + 1.0));
        }
        m_widthMulti = value;
    });
}

void EraWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    adjustSceneRect(m_widthMulti);
    if(m_widthMulti == -1)
    {
        m_slider->setSliderPosition(0);
        m_slider->setSliderPosition(-1);
    }
}

/*! Adjusts the size of the scene rect
 * \brief MainWindow::adjustSceneRect
 * \param value - double: adjust value
 */
void EraWidget::adjustSceneRect(double value)
{
    if(value == 0)
    {
        value = 1;
    }
    m_scene->setSceneRect(-(TIMELINE_BORDER * DIVISOR * value + 50 * value), (-m_view->height() - m_sceneHeightAdjust) / 2,
                          (2 * TIMELINE_BORDER * DIVISOR * value + 100 * value), m_view->height() - m_sceneHeightAdjust);
    m_scene->adjustWidthMultiplier(value);
}
