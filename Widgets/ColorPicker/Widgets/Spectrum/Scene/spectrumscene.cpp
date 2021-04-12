#include "spectrumscene.h"
#include "Widgets/ColorPicker/Widgets/Spectrum/Utils/colorspectrum.h"
#include "handleitem.h"
#include <QGraphicsPixmapItem>
#include <QDebug>

SpectrumScene::SpectrumScene(double viewWidth, QPixmap map, QObject *parent) : QGraphicsScene(parent),
    m_pressed(false),
    m_specWidth(map.width()),
    m_specHeight(map.height()),
    m_viewWidth(viewWidth)
{
    m_handle = new HandleItem;
    m_handle->setPos(map.width() / 2, map.height() / 2);
    m_item = new QGraphicsPixmapItem(map);
    addItem(m_item);
    addItem(m_handle);
}

void SpectrumScene::updateScene(double viewWidth, QPixmap map)
{
    m_viewWidth = viewWidth;
    double oldWidth = m_specWidth;
    m_specWidth = map.width();
    m_specHeight = map.height();
    m_handle->setPos(ColorSpectrum::findColor(m_specWidth, m_handle->getColor(oldWidth)), m_specHeight/2);
    m_item->setPixmap(map);
}

//EVENTS*********************************************************
void SpectrumScene::mouseMoveEvent(QGraphicsSceneMouseEvent* e)
{
    if(m_pressed && selectedItems().size() == 1)
    {
        emit colorChanged(m_handle->getColor(m_specWidth));
    }
    QGraphicsScene::mouseMoveEvent(e);
    m_handle->setY(m_specHeight / 2);
    if(m_handle->x() < 0) m_handle->setX(0);
    if(m_handle->x() > m_specWidth) m_handle->setX(m_viewWidth);
}

void SpectrumScene::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    m_pressed = true;
    QGraphicsScene::mousePressEvent(e);
}

void SpectrumScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
    m_pressed = false;
    QGraphicsScene::mouseReleaseEvent(e);
}

//SLOTS************************************************************
void SpectrumScene::setColor(const QColor& color)
{
    m_handle->setX(ColorSpectrum::findColor(m_specWidth, color));
}
