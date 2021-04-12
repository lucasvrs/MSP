#include "todolist.h"
#include "ui_todolist.h"
#include "todo.h"
#include "newentry.h"

/*!
 * \brief Constructor
 * \param parent
 */
ToDoList::ToDoList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToDoList)
  , m_reader("./../FinalMsp/Widgets/ToDoList/ToDo.xml")
  , m_writer("./../FinalMsp/Widgets/ToDoList/ToDo.xml")
{
    ui->setupUi(this);
    initiateGUI();
}

/*!
 * \brief Deconstructor
 */
ToDoList::~ToDoList()
{
    delete ui;
}
/*!
 * \brief gets data from xml-file
 */
void ToDoList::initiateList()
{
    for (const QDomElement &e : *m_reader.allElemsUnderRoot()) {
        if(e.nodeName() == "pending")
        {

            for(const QDomElement &cE : *m_reader.allElemsUnderElem(e))
            {
              m_taskNamesPending.append(cE.attribute("name"));
              for(const QDomElement &fE : *m_reader.allElemsUnderElem(cE))
              {
                  if(fE.tagName() == "date")
                  {
                      m_datePending.append(fE.text());
                  }
                  if(fE.tagName() == "prio")
                  {
                      m_prioPending.append(fE.text());
                  }
              }
            }
        }

        if(e.nodeName() == "done")
        {
            for(const QDomElement &cE : *m_reader.allElemsUnderElem(e))
            {
              m_taskNamesDone.append(cE.attribute("name"));
              for(const QDomElement &fE : *m_reader.allElemsUnderElem(cE))
              {
                  if(fE.tagName() == "date")
                  {
                      m_dateDone.append(fE.text());
                  }
                  if(fE.tagName() == "prio")
                  {
                      m_prioDone.append(fE.text());
                  }
              }
            }
        }



    }

    showLists();
}

/*!
 * \brief show lists
 */
void ToDoList::showLists()
{
    ui->tv_pending->setModel(NULL);
    m_toDoPending->populateData(m_taskNamesPending,m_prioPending,m_datePending);
    ui->tv_pending->setModel(m_toDoPending);
    ui->tv_pending->horizontalHeader()->setVisible(true);
    ui->tv_pending->show();

    ui->tv_done->setModel(NULL);
    m_toDoDone->populateData(m_taskNamesDone,m_prioDone,m_dateDone);
    ui->tv_done->setModel(m_toDoDone);
    ui->tv_done->horizontalHeader()->setVisible(true);
    ui->tv_done->show();
}
/*!
 * \brief sorted by priority
 */
void ToDoList::sortPrio()
{
 QList<int> low,middle,high;
 for (int i = 0; i < m_prioPending.length(); i++) {
     QString string = m_prioPending.at(i);
     if(string == "Niedrig")
     {
         low.append(i);
     }
     else if(string == "Mittel")
     {
         middle.append(i);

     }
     else if(string == "Hoch")
     {
         high.append(i);
     }

 }
 QList<QString> date,prio,task;

 for(int i : high)
 {
     date.append(m_datePending.at(i));
     prio.append(m_prioPending.at(i));
     task.append(m_taskNamesPending.at(i));
 }
 for(int i : middle)
 {
     date.append(m_datePending.at(i));
     prio.append(m_prioPending.at(i));
     task.append(m_taskNamesPending.at(i));
 }
 for(int i : low)
 {
     date.append(m_datePending.at(i));
     prio.append(m_prioPending.at(i));
     task.append(m_taskNamesPending.at(i));
 }

 m_datePending = date;
 m_prioPending = prio;
 m_taskNamesPending = task;

 showLists();



}

/*!
 * \brief sorted by date
 */
void ToDoList::sortDate()
{
  QMap<double, int> map;
  QList<double> list;
  QList<int> sorted;


  for (int i = 0; i< m_datePending.length(); i++) {
      QString string =  m_datePending.at(i).at(0);
      string += m_datePending.at(i).at(1);
      string += m_datePending.at(i).at(3);
      string += m_datePending.at(i).at(4);
      string += m_datePending.at(i).at(6);
      string += m_datePending.at(i).at(7);
      string += m_datePending.at(i).at(8);
      string += m_datePending.at(i).at(9);

      double date = string.toDouble();
      while(map.value(date) != NULL)
      {
          date += 0.00001;
      }

      map.insert(date, i);
      list.append(date);
 }

  qSort(list);

  for(double i : list){
      sorted.append(map.value(i));
  }

  QList<QString> date,prio,task;

  for (int i : sorted) {
      date.append(m_datePending.at(i));
      prio.append(m_prioPending.at(i));
      task.append(m_taskNamesPending.at(i));
  }

  m_datePending = date;
  m_prioPending = prio;
  m_taskNamesPending = task;

  showLists();

}

/*!
 * \brief sorted alphabetically
 */
void ToDoList::sortAlph()
{
  QMap<QString, int> map;
  QList<QString> list;
  QList<int> sorted;

  for (int i = 0; i< m_taskNamesPending.length(); i++) {
      map.insert(m_taskNamesPending.at(i), i);
      list.append(m_taskNamesPending.at(i));
  }

  qSort(list);

  for(QString string : list){
      sorted.append(map.value(string));

  }

  QList<QString> date,prio,task;

  for (int i : sorted) {
      date.append(m_datePending.at(i));
      prio.append(m_prioPending.at(i));
      task.append(m_taskNamesPending.at(i));
  }

  m_datePending = date;
  m_prioPending = prio;
  m_taskNamesPending = task;

  showLists();
}

/*!
 * \brief converts date to string
 * \param newEntry
 * \return date in string
 */
QString ToDoList::dateToString(NewEntry *newEntry)
{
    QString date;
    if(newEntry->date().day() >= 10)
    {
        date = date + QString::number(newEntry->date().day()) + ".";
    }
    else
    {
        date = date + "0" + QString::number(newEntry->date().day()) + ".";
    }
    if(newEntry->date().month() >= 10)
    {
        date = date + QString::number(newEntry->date().month()) + ".";
    }
    else
    {
        date = date + "0" + QString::number(newEntry->date().month()) + ".";
    }
    return date = date + QString::number(newEntry->date().year());

}

/*!
 * \brief converts string to date
 * \param string
 * \return date
 */
QDate ToDoList::StringToDate(QString string)
{
    QDate date;
    QString y = string.at(6);
            y += string.at(7);
            y += string.at(8);
            y += string.at(9);
    QString m = string.at(3);
            m += string.at(4);
    QString d = string.at(0);
            d += string.at(1);
    date.setDate(y.toInt(), m.toInt(), d.toInt());

    return date;


}

/*!
 * \brief initiate Gui - connect btn with signals
 */
void ToDoList::initiateGUI()
{
    connect(ui->btn_edit, SIGNAL(clicked()), this, SLOT(edit()));

    connect(ui->btn_add, SIGNAL(clicked()), this, SLOT(add()));
    connect(ui->btn_del, SIGNAL(clicked()), this, SLOT(del()));
    connect(ui->btn_done, SIGNAL(clicked()), this, SLOT(done()));
    connect(ui->cb_pending, &QComboBox::currentTextChanged, [this](QString selection){
        sort(selection);
    });
    connect(ui->btn_up, SIGNAL(clicked()), this, SLOT(up()));
    connect(ui->btn_down, SIGNAL(clicked()), this, SLOT(down()));

    initiateList();

}

/*!
 * \brief adds new Entry to ToDo-List
 */
void ToDoList::add()
{

  NewEntry *newEntry = new NewEntry();
  newEntry->setModal(true);
  newEntry->exec();
  if(newEntry->task() != ""){
  QDomElement task = m_writer.createElement("task");
  task.setAttribute("name", newEntry->task());
  QDomNode node1 = m_writer.getRootElement()->childNodes().at(0);

      m_writer.appendElementUnderElement(node1,task);
      QString date = dateToString(newEntry);

      m_writer.appendElementUnderElement(task, "date", date);
      m_writer.appendElementUnderElement(task,"prio", newEntry->prio());

      m_taskNamesPending.append(newEntry->task());
      m_prioPending.append(newEntry->prio());
      m_datePending.append(date);

      showLists();
      m_writer.saveXML();


}

}

/*!
 * \brief deletes entry from ToDo-List
 */
void ToDoList::del()
{
  QModelIndex index_pen = ui->tv_pending->currentIndex();

  if(ui->tv_pending->selectionModel()->isSelected(index_pen))
  {
  QString string = m_taskNamesPending.at(index_pen.row());
  m_taskNamesPending.removeAt(index_pen.row());
  m_prioPending.removeAt(index_pen.row());
  m_datePending.removeAt(index_pen.row());
  showLists();

  for (const QDomElement &e : *m_reader.allElemsUnderRoot()) {
      if(e.nodeName() == "pending")
      {

          for(const QDomElement &cE : *m_reader.allElemsUnderElem(e))
          {
            if(cE.attribute("name") == string)
            {
                m_writer.removeElement(string, e.nodeName(), e.parentNode().nodeName());
            }
      }

      }
  }
}

  QModelIndex index_don = ui->tv_done->currentIndex();

  if(ui->tv_done->selectionModel()->isSelected(index_don))
  {
  QString string = m_taskNamesDone.at(index_don.row());
  m_taskNamesDone.removeAt(index_don.row());
  m_prioDone.removeAt(index_don.row());
  m_dateDone.removeAt(index_don.row());
  showLists();

  for (const QDomElement &e : *m_reader.allElemsUnderRoot()) {
      if(e.nodeName() == "done")
      {

          for(const QDomElement &cE : *m_reader.allElemsUnderElem(e))
          {
            if(cE.attribute("name") == string)
            {
                m_writer.removeElement(string, e.nodeName(), e.parentNode().nodeName());
            }
      }

      }
  }
}


}

/*!
 * \brief moves the entry to the done list
 */
void ToDoList::done()
{

    QModelIndex index = ui->tv_pending->currentIndex();

    if(ui->tv_pending->selectionModel()->isSelected(index))
    {

    QString string = m_taskNamesPending.at(index.row());

    m_taskNamesDone.append(m_taskNamesPending.at(index.row()));
    m_prioDone.append(m_prioPending.at(index.row()));
    m_dateDone.append(m_datePending.at(index.row()));

    QDomElement task = m_writer.createElement("task");
    task.setAttribute("name", m_taskNamesPending.at(index.row()));
    QDomNode node1 = m_writer.getRootElement()->childNodes().at(1);
    m_writer.appendElementUnderElement(node1,task);
    m_writer.appendElementUnderElement(task, "date", m_datePending.at(index.row()));
    m_writer.appendElementUnderElement(task,"prio", m_prioPending.at(index.row()));

    m_taskNamesPending.removeAt(index.row());
    m_prioPending.removeAt(index.row());
    m_datePending.removeAt(index.row());
    showLists();

    for (const QDomElement &e : *m_reader.allElemsUnderRoot()) {
        if(e.nodeName() == "pending")
        {

            for(const QDomElement &cE : *m_reader.allElemsUnderElem(e))
            {
              if(cE.attribute("name") == string)
              {
                  m_writer.removeElement(string, e.nodeName(), e.parentNode().nodeName());
              }
        }

        }

}

}

}

/*!
 * \brief edited entry
 */
void ToDoList::edit()
{
   QModelIndex index_pen = ui->tv_pending->currentIndex();
   if(ui->tv_pending->selectionModel()->isSelected(index_pen))
   {

    QString string = m_taskNamesPending.at(index_pen.row());
    QList<QString> task, dat, prio;
    QDate date = StringToDate(m_datePending.at(index_pen.row()));

    NewEntry *newEntry = new NewEntry(nullptr, m_taskNamesPending.at(index_pen.row()), m_prioPending.at(index_pen.row()),date);
    newEntry->setModal(true);
    newEntry->exec();



    for (int i = 0;i < m_taskNamesPending.length(); i++) {

       if(i == index_pen.row())
       {
         task.append(newEntry->task());
         prio.append(newEntry->prio());
         dat.append(dateToString(newEntry));
       }
       else
       {
         task.append(m_taskNamesPending.at(i));
         prio.append(m_prioPending.at(i));
         dat.append(m_datePending.at(i));

       }


    }



    m_taskNamesPending = task;
    m_prioPending = prio ;
    m_datePending = dat;
    showLists();

   for (const QDomElement &e : *m_reader.allElemsUnderRoot()) {
       if(e.nodeName() == "pending")
       {

           for(const QDomElement &cE : *m_reader.allElemsUnderElem(e))
           {
             if(cE.attribute("name") == string)
             {
                 m_writer.removeElement(string, e.nodeName(), e.parentNode().nodeName());
             }
       }

       }
   }

   QDomElement newtask = m_writer.createElement("task");
   newtask.setAttribute("name", newEntry->task());
   QDomNode node1 = m_writer.getRootElement()->childNodes().at(0);

       m_writer.appendElementUnderElement(node1,newtask);
       QString newdate = dateToString(newEntry);

       m_writer.appendElementUnderElement(newtask, "date", newdate);
       m_writer.appendElementUnderElement(newtask,"prio", newEntry->prio());
       showLists();
       m_writer.saveXML();




}
}

/*!
 * \brief sorts list by string
 * \param sort
 */
void ToDoList::sort(QString &sort)
{
    if(sort == "Prio")
    {
        sortPrio();

    }
    else if(sort == "Alpha")
    {
        sortAlph();
    }
    else if(sort == "Date")
    {
        sortDate();
    }


}

/*!
 * \brief moves entry up
 */
void ToDoList::up()
{
    QModelIndex index_pen = ui->tv_pending->currentIndex();

    if(ui->tv_pending->selectionModel()->isSelected(index_pen) && index_pen.row() != 0)
    {
        QList<QString> task,date,prio;
        for (int i = 0;i< m_taskNamesPending.length(); i++) {
            if(i == index_pen.row()-1)
            {
                task.append(m_taskNamesPending.at(i+1));
                prio.append(m_prioPending.at(i+1));
                date.append(m_datePending.at(i+1));

                task.append(m_taskNamesPending.at(i));
                prio.append(m_prioPending.at(i));
                date.append(m_datePending.at(i));
                i+=1;

            }
            else
            {
                task.append(m_taskNamesPending.at(i));
                prio.append(m_prioPending.at(i));
                date.append(m_datePending.at(i));

            }
        }

        m_taskNamesPending = task;
        m_prioPending = prio;
        m_datePending = date;
        showLists();


  }

    QModelIndex index_don = ui->tv_done->currentIndex();

    if(ui->tv_done->selectionModel()->isSelected(index_don) && index_don.row() != 0)
    {
        QList<QString> task,date,prio;
        for (int i = 0;i< m_taskNamesDone.length(); i++) {

            if(i == index_don.row()-1)
            {
                task.append(m_taskNamesDone.at(i+1));
                prio.append(m_prioDone.at(i+1));
                date.append(m_dateDone.at(i+1));

                task.append(m_taskNamesDone.at(i));
                prio.append(m_prioDone.at(i));
                date.append(m_dateDone.at(i));
                i+=1;

            }
            else
            {

                task.append(m_taskNamesDone.at(i));
                prio.append(m_prioDone.at(i));
                date.append(m_dateDone.at(i));

            }
        }

        m_taskNamesDone = task;
        m_prioDone = prio;
        m_dateDone = date;
        showLists();


        showLists();


  }

}
/*!
 * \brief moves entry down
 */
void ToDoList::down()
{
    QModelIndex index_pen = ui->tv_pending->currentIndex();

    if(ui->tv_pending->selectionModel()->isSelected(index_pen) && index_pen.row() != m_taskNamesPending.length() - 1)
    {
        QList<QString> task,date,prio;
        for (int i = 0;i< m_taskNamesPending.length(); i++) {
            if(i == index_pen.row())
            {
                task.append(m_taskNamesPending.at(i+1));
                prio.append(m_prioPending.at(i+1));
                date.append(m_datePending.at(i+1));

                task.append(m_taskNamesPending.at(i));
                prio.append(m_prioPending.at(i));
                date.append(m_datePending.at(i));
                i+=1;

            }
            else
            {
                task.append(m_taskNamesPending.at(i));
                prio.append(m_prioPending.at(i));
                date.append(m_datePending.at(i));

            }
        }

        m_taskNamesPending = task;
        m_prioPending = prio;
        m_datePending = date;
        showLists();


}
    QModelIndex index_don = ui->tv_done->currentIndex();

    if(ui->tv_done->selectionModel()->isSelected(index_don) && index_don.row() != m_taskNamesDone.length() - 1)
    {

        QList<QString> task,date,prio;
        for (int i = 0;i< m_taskNamesDone.length(); i++) {
            if(i == index_don.row())
            {
                task.append(m_taskNamesDone.at(i+1));
                prio.append(m_prioDone.at(i+1));
                date.append(m_dateDone.at(i+1));

                task.append(m_taskNamesDone.at(i));
                prio.append(m_prioDone.at(i));
                date.append(m_dateDone.at(i));
                i+=1;
            }
            else
            {
                task.append(m_taskNamesDone.at(i));
                prio.append(m_prioDone.at(i));
                date.append(m_dateDone.at(i));

            }
        }

        m_taskNamesDone = task;
        m_prioDone = prio;
        m_dateDone = date;
        showLists();


        showLists();


  }

}
