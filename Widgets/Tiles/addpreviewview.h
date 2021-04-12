#ifndef ADDPREVIEWVIEW_H
#define ADDPREVIEWVIEW_H

#include <QGraphicsView>

class AddPreviewScene;
class TileItem;

class AddPreviewView : public QGraphicsView
{
    Q_OBJECT

public:
    AddPreviewView(QWidget* parent = nullptr);

private:
    AddPreviewScene* m_scene;

protected:
    void resizeEvent(QResizeEvent* e) override;
    void scrollContentsBy(int, int v) override;

signals:
    void addTile(TileItem* w);
};

#endif // ADDPREVIEWVIEW_H
