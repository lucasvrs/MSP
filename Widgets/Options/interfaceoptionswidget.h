#ifndef INTERFACEOPTIONSWIDGET_H
#define INTERFACEOPTIONSWIDGET_H

#include <QWidget>

class InterfaceOptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InterfaceOptionsWidget(QWidget *parent = nullptr);

signals:
    void closeOptions();
    void changeStyle(int mode);
};

#endif // INTERFACEOPTIONSWIDGET_H
