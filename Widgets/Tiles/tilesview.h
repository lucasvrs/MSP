#ifndef TILESVIEW_H
#define TILESVIEW_H

#include <QGraphicsView>

class TileScene;

class TilesView : public QGraphicsView
{
    Q_OBJECT
public:
    TilesView(QWidget* parent = nullptr);

private:
    TileScene* m_scene;

protected:
    void resizeEvent(QResizeEvent* e) override;
    void scrollContentsBy(int, int v) override;

signals:
    void showSubject(const QString& title);
};

#endif // TILESVIEW_H
