#ifndef TODOLIST_H
#define TODOLIST_H

#include <QDialog>
#include "Xml/xmlreader.h"
#include "Xml/xmlwriter.h"
#include "todo.h"
#include "newentry.h"


namespace Ui {
class ToDoList;
}

class ToDoList : public QWidget
{
    Q_OBJECT

public:

    ToDoList(QWidget *parent = nullptr);
    ~ToDoList();
    void initiateList();
    void showLists();
    void sortPrio();
    void sortDate();
    void sortAlph();
    QString dateToString(NewEntry *newEntry);
    QDate StringToDate(QString string);
    void initiateGUI();


public slots:

    void add();
    void del();
    void done();
    void edit();
    void sort(QString& sort);
    void up();
    void down();




private:

    Ui::ToDoList *ui;
    XMLReader m_reader;
    XMLWriter m_writer;

    QList<QString> m_taskNamesPending;
    QList<QString> m_prioPending;
    QList<QString> m_datePending;

    QList<QString> m_taskNamesDone;
    QList<QString> m_prioDone;
    QList<QString> m_dateDone;

    ToDo *m_toDoDone = new ToDo();
    ToDo *m_toDoPending = new ToDo();

};

#endif // TODOLIST_H
