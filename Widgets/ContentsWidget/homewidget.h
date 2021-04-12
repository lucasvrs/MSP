#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>

class TileItem;

class HomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = nullptr);

private:

signals:
    void showSubject(const QString& title, QList<TileItem*> list);
};

#endif // HOMEWIDGET_H
