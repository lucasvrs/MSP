#ifndef ERAVIEW_H
#define ERAVIEW_H

#include <QGraphicsView>

class EraView : public QGraphicsView
{
    Q_OBJECT
public:
    EraView(QWidget *parent = nullptr);

protected:
    void scrollContentsBy(int, int) override;
    void wheelEvent(QWheelEvent* e) override;
};

#endif // ERAVIEW_H
