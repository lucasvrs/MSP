#ifndef NEWENTRY_H
#define NEWENTRY_H

#include <QDialog>
#include <QDate>

namespace Ui {
class NewEntry;
}

class NewEntry : public QDialog
{
    Q_OBJECT

public:
    explicit NewEntry(QWidget *parent = nullptr, QString task = "", QString prio = "Niedrig", QDate date = QDate::currentDate());
    ~NewEntry();

     QString task() ;
     QString prio()  ;
     QDate date() ;

     void setTask(QString task);
     void setDate(QDate date);
     void setPrio(QString prio);
public slots:
    void btn_saveClicked();
    void btn_backClicked();
    bool eventFilter(QObject *obj, QEvent *event);


private:
    Ui::NewEntry *ui;
    QDate m_date;
    QString m_task, m_dateString;
    QString m_prio;
};

#endif // NEWENTRY_H
