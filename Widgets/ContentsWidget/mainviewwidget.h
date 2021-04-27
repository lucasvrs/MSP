#ifndef MAINVIEWWIDGET_H
#define MAINVIEWWIDGET_H

#include <QStackedWidget>

class MainViewWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit MainViewWidget(QWidget *parent = nullptr);

private:
    QWidget* m_app;

signals:
    void newTitle(const QString& title);
    void setPrevWidget(QWidget* w);
};

#endif // MAINVIEWWIDGET_H
