#ifndef SPECTRUMSVIEW_H
#define SPECTRUMSVIEW_H

#include <QGraphicsView>

class SpectrumsView : public QGraphicsView
{
    Q_OBJECT
public:
    SpectrumsView(QWidget *parent = nullptr);

protected:
    void scrollContentsBy(int, int) override;
};

#endif // SPECTRUMSVIEW_H
