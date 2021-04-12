/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "tilescene.h"
#include "tileitem.h"
#include "tileconstants.h"
#include "tilefactory.h"
#include "addtile.h"
#include "createcollectiondialog.h"
#include "tilefactory.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QMenu>

TileScene::TileScene(QObject *parent) : QGraphicsScene(parent), m_dialog(nullptr)
{
    m_factory = new TileFactory;
}

//SLOTS**********************************************
/*! Adds items to scene
 * \brief TileScene::addItems
 */
void TileScene::addItems()
{
    m_tiles = m_factory->tiles();
    m_tileLength = ((m_width - 20) - (m_cols + 1) * SPACING) / m_cols;
    double xStart = -(m_cols/2.0) * m_tileLength - (m_cols/2.0) * SPACING;
    double x = xStart;
    double height = 0;
    int row = 0;
    for(int i = 0; i < m_tiles.size(); i++)
    {
        if(i % m_cols == 0)
        {
            row++;
            x = xStart;
        }
        TileItem* tile = m_tiles.at(i);
        tile->setWidth(m_tileLength);
        tile->setHeight(m_tileLength);
        tile->setPos(x, height + (m_tileLength + SPACING) * row);
        x += (m_tileLength + SPACING);
        addItem(tile);
    }
    if(m_tiles.size() % m_cols == 0)
    {
        row++;
        x = xStart;
    }
    AddTile* addTile = new AddTile;
    addTile->setWidth(m_tileLength);
    addTile->setHeight(m_tileLength);
    addTile->setPos(x, height + (m_tileLength + SPACING) * row);
    x += (m_tileLength + SPACING);
    addItem(addTile);
}

/*! Deletes all items from scene
 * \brief TileScene::deleteItems
 */
void TileScene::deleteItems()
{
    for(QGraphicsItem* item : items())
    {
        removeItem(item);
        delete item;
    }
}

/*! Updates the tiles of the scene
 * \brief TileScene::updateScene
 * \param w - Width of SceneRect
 */
void TileScene::updateScene(double w)
{
    m_width = w;
    deleteItems();
    addItems();
    int add = (m_tiles.size() + 1)%m_cols;
    int fac = ((m_tiles.size() + 1) - ((m_tiles.size() + 1)%m_cols)) / m_cols;
    if(add != 0)
    {
        fac++;
    }
    m_height = fac * m_tileLength + (fac + 2) * SPACING;
    setSceneRect(QRectF(-w/2 - m_tileLength / 2 - (SPACING + 5), m_tileLength/2, w, m_height));
}

//EVENTS**************************************************************************************
void TileScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
    QGraphicsItem* item = itemAt(e->scenePos(), QTransform());
    if(item != nullptr)
    {
        TileItem* tile = static_cast<TileItem*>(item);
        if(e->button() == Qt::MouseButton::LeftButton)
        {
            if(tile->text() == "+")
            {
                if(m_dialog == nullptr)
                {
                    m_dialog = new CreateCollectionDialog;
                    m_dialog->show();
                    connect(m_dialog, &CreateCollectionDialog::newTile, [this]()
                    {
                        updateScene(m_width);
                    });
                    connect(m_dialog, &CreateCollectionDialog::closed, [this]()
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
                emit showSubject(tile->text(), tile->previews());
            }
        }
    }
    QGraphicsScene::mouseReleaseEvent(e);
}

void TileScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* e)
{
    QGraphicsItem* item = itemAt(e->scenePos(), QTransform());
    if(item != nullptr)
    {
        TileItem* tile = static_cast<TileItem*>(item);
        QMenu menu;
        menu.addAction("Delete", [this, tile]()
        {
            removeTile(tile);
        });
        menu.exec(e->screenPos());
    }
    QGraphicsScene::contextMenuEvent(e);
}

void TileScene::removeTile(TileItem* tile)
{
    TileFactory fac;
    fac.deleteTile(tile->text(), tile->id());
    updateScene(m_width);
}
