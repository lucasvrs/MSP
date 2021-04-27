#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QGraphicsSceneMouseEvent>
#include <QStackedWidget>
#include "widgetitem.h"
#include "mainhelpwidget.h"
#include "subjecthelpwidget.h"

class HelpWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit HelpWidget(QWidget *parent = nullptr);

    void changeSite(WidgetItem *item);
    void homeScreen();

private:
    MainHelpWidget* w;
    SubjectHelpWidget *s;

protected:
    void resizeEvent(QResizeEvent* e) override;

};

#endif // HELPWIDGET_H
