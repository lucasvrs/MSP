#ifndef MAINVIEWWIDGET_H
#define MAINVIEWWIDGET_H

#include <QStackedWidget>

class MainViewWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit MainViewWidget(QWidget *parent = nullptr);

signals:

};

#endif // MAINVIEWWIDGET_H
