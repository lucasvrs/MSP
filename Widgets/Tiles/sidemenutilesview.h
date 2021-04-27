#ifndef SIDEMENUTILESVIEW_H
#define SIDEMENUTILESVIEW_H

#include <QGraphicsView>

class SideMenuTileScene;
class TileItem;

class SideMenuTilesView : public QGraphicsView
{
    Q_OBJECT
public:
    SideMenuTilesView(QWidget* parent = nullptr);

private:
    SideMenuTileScene* m_scene;

protected:
    void resizeEvent(QResizeEvent* e) override;
    void scrollContentsBy(int, int v) override;

signals:
    void showWidget(QWidget* w);
    void showWidgetSep(QWidget* w);
    void addTile();

public slots:
    void setPreview(QList<TileItem*> previews);
    void setTitle(const QString& title);
    void setId(int id);
};

#endif // SIDEMENUTILESVIEW_H
