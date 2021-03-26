#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>

class HomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = nullptr);

private:

signals:
    void showSubject(const QString& title);
};

#endif // HOMEWIDGET_H
