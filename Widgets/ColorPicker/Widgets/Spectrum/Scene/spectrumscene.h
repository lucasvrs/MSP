#ifndef SPECTRUMSCENE_H
#define SPECTRUMSCENE_H

#include <QGraphicsScene>

class HandleItem;

class SpectrumScene : public QGraphicsScene
{
    Q_OBJECT

public:
    SpectrumScene(double viewWidth, QPixmap map, QObject* parent = nullptr);
    void updateScene(double viewWidth, QPixmap map);

private:
    bool m_pressed;
    QGraphicsPixmapItem* m_item;
    HandleItem* m_handle;
    double m_specWidth;
    double m_specHeight;
    double m_viewWidth;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* e) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* e) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e) override;

signals:
    void colorChanged(const QColor& color);

public slots:
    void setColor(const QColor& color);
};

#endif // SPECTRUMSCENE_H
