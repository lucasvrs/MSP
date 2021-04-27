/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "homewidget.h"
#include "Widgets/Tiles/tilesview.h"
#include <QVBoxLayout>
#include <QDebug>

HomeWidget::HomeWidget(QWidget *parent) : QWidget(parent)
{
    //defines layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    m_view = new TilesView;
    layout->addWidget(m_view);

    //connects
    connect(m_view, &TilesView::showSubject, [this](const QString& title, QList<TileItem*> list, int id)
    {
        emit showSubject(title, list, id);
        emit setPrevWidget(this);
    });
}

//SLOTS***************************************************
void HomeWidget::addTile()
{
    m_view->updateTiles();
}
