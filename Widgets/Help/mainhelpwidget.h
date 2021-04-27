#ifndef MAINHELPWIDGET_H
#define MAINHELPWIDGET_H

#include <QScrollArea>
#include "widgetitem.h"

class MainHelpContentsWidget;

class MainHelpWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit MainHelpWidget(QWidget *parent = nullptr);

private:
    MainHelpContentsWidget* m_main;

signals:
    void emitSignal(WidgetItem* item);

public slots:
    void setWidth(double width);
    void setHeight(double height);
};

#endif // MAINHELPWIDGET_H
