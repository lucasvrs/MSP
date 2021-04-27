/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "sidemenutilescene.h"
#include "tileitem.h"
#include "addtile.h"
#include "addpreviewdialog.h"
#include "tilefactory.h"
#include <QMenu>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

SideMenuTileScene::SideMenuTileScene(QObject *parent) :
    QGraphicsScene(parent),
    m_alreadyAdded(false),
    m_dialog(nullptr)
{

}

//SLOTS**********************************************
void SideMenuTileScene::addItems(QList<TileItem*> tiles)
{
    m_tiles = tiles;
    m_tileLength = ((m_width - 20) - 2 * 10);
    double xStart = -0.5 * m_tileLength - 1 * 10;
    double x = xStart;
    double height = 0;
    int row = 0;
    for(int i = 0; i < tiles.size(); i++)
    {
        if(i % 1 == 0)
        {
            row++;
            x = xStart;
        }
        TileItem* tile = tiles.at(i);
        tile->setWidth(m_tileLength);
        tile->setHeight(m_tileLength);
        tile->setPos(x, height + (m_tileLength + 10) * row);
        x += (m_tileLength + 10);
        if(!m_alreadyAdded) addItem(tile);
    }
    if(m_tiles.size() < 4)
    {
        if(m_tiles.size() % 1 == 0)
        {
            row++;
            x = xStart;
        }
        AddTile* addTile = new AddTile;
        addTile->setWidth(m_tileLength);
        addTile->setHeight(m_tileLength);
        addTile->setPos(x, height + (m_tileLength + 10) * row);
        x += (m_tileLength + 10);
        addItem(addTile);
    }
}

/*! Deletes all items from scene
 * \brief TileScene::deleteItems
 */
void SideMenuTileScene::deleteItems()
{
    for(QGraphicsItem* item : items())
    {
        removeItem(item); //although it removes the item from the scene, the pointer still is active
        //delete item;
    }
}

void SideMenuTileScene::updateScene(double w)
{
    m_alreadyAdded = true;
    m_width = w;
    addItems(m_tiles);
    int fac = ((m_tiles.size() + 1) - ((m_tiles.size() + 1)%1));
    m_height = fac * m_tileLength + (fac + 2);
    setSceneRect(QRectF(-w/2 - m_tileLength / 2 - (10 - 5), m_tileLength/2, w, m_height));
}

void SideMenuTileScene::setPreview(QList<TileItem*> previews)
{
    deleteItems();
    m_alreadyAdded = false;
    addItems(previews);
}

//EVENTS*************************************************************************
void SideMenuTileScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
    QGraphicsItem* item = itemAt(e->scenePos(), QTransform());
    if(item != nullptr)
    {
        if(e->button() == Qt::LeftButton)
        {
            TileItem* tile = static_cast<TileItem*>(item);
            if(tile->text() == "+")
            {
                if(m_dialog == nullptr)
                {
                    m_dialog = new AddPreviewDialog;
                    m_dialog->show();
                    connect(m_dialog, &AddPreviewDialog::addTile, [this](TileItem* tile)
                    {
                        bool add = true;
                        for(TileItem* t : m_tiles)
                        {
                            if(t->text() == tile->text())
                            {
                                add = false;
                            }
                        }
                        if(add)
                        {
                            editTile(tile);
                            emit addTile();
                        }
                    });
                    connect(m_dialog, &AddPreviewDialog::closed, [this]()
                    {
                        m_dialog = nullptr;
                    });
                }
                else
                {
                    m_dialog->raise();
                }
            }
            else
            {
                QWidget* w = tile->widget();
                if(w != nullptr) emit showWidget(w);
            }
        }
    }
    QGraphicsScene::mouseReleaseEvent(e);
}

void SideMenuTileScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* e)
{
    QGraphicsItem* item = itemAt(e->scenePos(), QTransform());
    if(item != nullptr)
    {
        TileItem* tile = static_cast<TileItem*>(item);
        for(TileItem* t : m_tiles)
        {
            if(t == tile)
            {
                tile->setId(t->id());
                break;
            }
        }
        QMenu menu;
        menu.addAction("Delete", [this, tile]()
        {
            removeTile(tile);
        });
        menu.exec(e->screenPos());
    }
    QGraphicsScene::contextMenuEvent(e);
}

void SideMenuTileScene::editTile(TileItem* tile)
{
    TileFactory fac;
    fac.addAppToTile(m_title, m_id, tile->text(), tile->id());
}

void SideMenuTileScene::setTitle(const QString& title)
{
    m_title = title;
}

void SideMenuTileScene::setId(int id)
{
    m_id = id;
}

void SideMenuTileScene::removeTile(TileItem* tile)
{
    TileFactory fac;
    fac.deletePreviewTile(m_title, m_id, tile->text(), tile->id());
    emit addTile();
}
