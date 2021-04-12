#include "newentry.h"
#include "ui_newentry.h"
#include <QDebug>

/*!
 * \brief Constructor
 * \param parent
 * \param task name of task
 * \param prio prioritie
 * \param date date
 */
NewEntry::NewEntry(QWidget *parent, QString task, QString prio, QDate date) :
    QDialog(parent),
    ui(new Ui::NewEntry)
   ,m_date(date)
   ,m_task(task)
   ,m_prio(prio)


{
    ui->setupUi(this);
    if(this->task() == "")
    {
    ui->de_date->setDateTime(QDateTime::currentDateTime());
    }
    else
    {
        const QDate date = this->date();
        ui->de_date->setDate(date);
        ui->cb_prio->setEditText(this->prio());
        ui->te_task->setText(this->task());
    }


    connect(ui->btn_save, SIGNAL(clicked()), this, SLOT(btn_saveClicked()));

}
/*!
 * \brief Deconstructor
 */
NewEntry::~NewEntry()
{
    delete ui;
}


/*!
 * \brief saves data and close window
 */
void NewEntry::btn_saveClicked()
{

    m_date = ui->de_date->date();
    m_task = ui->te_task->toPlainText();
    m_prio = ui->cb_prio->currentText();
    this->close();
}
/*!
 * \brief close the window
 */
void NewEntry::btn_backClicked()
{
    this->close();
}

bool NewEntry::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::Close)
    {
        this->setTask("");
        return true;
    }
    return QDialog::eventFilter(obj, event);
}
/*!
 * \brief m_date getter
 * \return m_date
 */
QDate NewEntry::date()
{
    return m_date;
}

/*!
 * \brief m_prio getter
 * \return m_prio
 */
QString NewEntry::prio()
{
    return m_prio;
}
/*!
 * \brief m_task getter
 * \return m_task
 */
QString NewEntry::task()
{
    return m_task;
}
/*!
 * \brief m_task setter
 * \param task new task
 */
void NewEntry::setTask(QString task)
{
    m_task = task;
}
/*!
 * \brief m_date setter
 * \param date new date
 */
void NewEntry::setDate(QDate date)
{
    m_date = date;
}
/*!
 * \brief m_prio setter
 * \param prio new prio
 */
void NewEntry::setPrio(QString prio)
{
    m_prio = prio;
}

