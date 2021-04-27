#ifndef SUBJECTHELPWIDGET_H
#define SUBJECTHELPWIDGET_H

#include <QScrollArea>
#include "widgetitem.h"

class SubjectHelpContentsWidget;

class SubjectHelpWidget  : public QScrollArea
{
    Q_OBJECT
public:
    explicit SubjectHelpWidget(WidgetItem *item = nullptr,QWidget *parent = nullptr );

private:
    SubjectHelpContentsWidget* m_subject;

signals:
    void emitSignal();

public slots:
    void setWidth(double width);
};

#endif // SUBJECTHELPWIDGET_H
