#ifndef PREVIEWTILESVIEW_H
#define PREVIEWTILESVIEW_H

#include <QGraphicsView>

class PreviewTileScene;

class PreviewTilesView : public QGraphicsView
{
    Q_OBJECT

public:
    PreviewTilesView(QWidget* parent = nullptr);

private:
    PreviewTileScene* m_scene;

protected:
    void resizeEvent(QResizeEvent* e) override;
    void scrollContentsBy(int, int v) override;

signals:
    void showWidget(QWidget* w);
};

#endif // PREVIEWTILESVIEW_H
