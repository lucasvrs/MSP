#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget *parent = nullptr);

protected:
    void scrollContentsBy(int, int) override;
    void resizeEvent(QResizeEvent* e) override;
};

#endif // VIEW_H
