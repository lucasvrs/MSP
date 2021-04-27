#ifndef SUBJECTHELPCONTENTSWIDGET_H
#define SUBJECTHELPCONTENTSWIDGET_H

#include <QWidget>
#include "widgetitem.h"

class QVBoxLayout;
class QLabel;

class SubjectHelpContentsWidget : public QWidget
{
    Q_OBJECT
public:
    SubjectHelpContentsWidget(WidgetItem *item = nullptr, QWidget *parent = nullptr);

private:
     QVBoxLayout *m_layout;
     QLabel* m_labelName;
     QLabel* m_description;
     QLabel * m_pictureLabel;
public slots:
     void btn_clicked();
     void setWidth(double width);

signals:
        void emitSignal();


};

#endif // SUBJECTHELPCONTENTSWIDGET_H
