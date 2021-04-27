#ifndef WIDGETITEM_H
#define WIDGETITEM_H

#include <qwidget.h>

class QLabel;

struct Shortcut{
   QString shorty;
   QString shortyFunc;

};

class WidgetItem : public QWidget
{
    Q_OBJECT

public:
    WidgetItem(QWidget *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    QString picLink() const;
    void setPicLink(const QString &picLink);

    QPixmap map() const;
    void setMap(const QPixmap &map);

    QString func() const;
    void setFunc(const QString &func);

    QList<Shortcut> shortList() const;
    void setShortList(const QList<Shortcut> &shortList);

public slots:
    void updatePixmap();
signals:
    void emitSignal(WidgetItem* item);


private:
     QString m_name;
     QString m_description;
     QString m_picLink;
     QLabel* m_line;
     QLabel* m_pic;
     QPixmap m_map;
     QString m_func;
     QList<Shortcut> m_shortList;

protected:
     void paintEvent(QPaintEvent*) override;
     void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // WIDGETITEM_H
