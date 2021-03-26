#include "previewtilescene.h"
#include "tileconstants.h"
#include "tileitem.h"
#include "previewtilefactory.h"
#include "addtile.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

PreviewTileScene::PreviewTileScene(QObject *parent) : QGraphicsScene(parent)
{
    m_factory = new PreviewTileFactory;
}

//SLOTS**********************************************
/*! Adds items to scene
 * \brief TileScene::addItems
 */
void PreviewTileScene::addItems()
{
    m_tiles = m_factory->previewTiles();
    m_tileLength = ((m_width - 20) - 11 * SPACING) / 10;
    double xStart = -5 * m_tileLength - 5 * SPACING;
    double x = xStart;
    double height = 0;
    int row = 0;
    for(int i = 0; i < m_tiles.size(); i++)
    {
        if(i % 10 == 0)
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
    if(m_tiles.size() % 10 == 0)
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
void PreviewTileScene::deleteItems()
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
void PreviewTileScene::updateScene(double w)
{
    m_width = w;
    deleteItems();
    addItems();
    int add = (m_tiles.size() + 1)%10;
    int fac = ((m_tiles.size() + 1) - ((m_tiles.size() + 1)%10)) / 10;
    if(add != 0)
    {
        fac++;
    }
    m_height = fac * m_tileLength + (fac + 2) * SPACING;
    setSceneRect(QRectF(-w/2 - m_tileLength / 2 - (SPACING - 5), m_tileLength/2, w, m_height));
}

//EVENTS**************************************************************************************
void PreviewTileScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
    QGraphicsItem* item = itemAt(e->scenePos(), QTransform());
    if(item != nullptr)
    {
        TileItem* tile = static_cast<TileItem*>(item);
        QWidget* w = tile->widget();
        if(w != nullptr) emit showWidget(w);
    }
    QGraphicsScene::mouseReleaseEvent(e);
}
