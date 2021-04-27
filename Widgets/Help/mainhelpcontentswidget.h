#ifndef MAINHELPCONTENTSWIDGET_H
#define MAINHELPCONTENTSWIDGET_H

#include <QWidget>
#include "widgetitem.h"

class QVBoxLayout;
class QLabel;
class QGridLayout;
class QTextEdit;

class MainHelpContentsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainHelpContentsWidget(QWidget *parent = nullptr);

signals:
    void emitSignal(WidgetItem* item);

public slots:
    void setWidth(double width);
    void setHeight(double height);

private:
    QVBoxLayout* m_layout;
    QLabel* label;
    QTextEdit* labelText;
    QLabel *m_pictureLabel;

    void addWidgets(QList<WidgetItem *> list);
    QList<WidgetItem*> m_list;
    QGridLayout *gridLayout;
    void updatePixmaps();

};

#endif // MAINHELPCONTENTSWIDGET_H
