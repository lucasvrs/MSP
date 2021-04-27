#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>

class TileItem;
class TilesView;

class HomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = nullptr);

private:
    TilesView* m_view;

signals:
    void showSubject(const QString& title, QList<TileItem*> list, int id);
    void setPrevWidget(QWidget* w);

public slots:
    void addTile();
};

#endif // HOMEWIDGET_H
