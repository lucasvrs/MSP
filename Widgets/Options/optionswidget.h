#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QTabWidget>

class InterfaceOptionsWidget;

class OptionsWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit OptionsWidget(QWidget *parent = nullptr);

private:
    InterfaceOptionsWidget* m_interface;

signals:

};

#endif // OPTIONSWIDGET_H
