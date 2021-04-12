#include "todo.h"

/*!
 * \brief Constructor
 */
ToDo::ToDo()
{

}
/*!
 * \brief populates Data
 * \param task_name QList<QString> with task-names
 * \param prio QList<QString> with priorities
 * \param date QList<QString> with dates
 */
void ToDo::populateData(const QList<QString> &task_name, const QList<QString> &prio, const QList<QString> &date)
{
    m_taskName.clear();
    m_taskName = task_name;
    m_prio.clear();
    m_prio = prio;
    m_date.clear();
    m_date = date;

}
/*!
 * \brief counts row
 * \param parent
 * \return number of rows
 */
int ToDo::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return m_taskName.length();
}
/*!
 * \brief counts column
 * \param parent
 * \return number of columns
 */
int ToDo::columnCount(const QModelIndex &parent) const
{
 Q_UNUSED(parent);
 return 3;
}
/*!
 * \brief sets data of Table
 * \param index place of the table
 * \param role place of the table
 * \return
 */
QVariant ToDo::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return m_taskName[index.row()];
    } else if (index.column() == 1) {
        return m_prio[index.row()];
    } else if(index.column() == 2)
    {
        return m_date[index.row()];
    }

    return QVariant();
}
/*!
 * \brief set headerdata
 * \param section position of header
 * \param orientation orientation of table
 * \param role role
 * \return  data of header
 */
QVariant ToDo::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString("Task");
        } else if (section == 1) {
            return QString("Prio");
        }
        else if(section == 2){
            return QString("Date");
        }
    }
    return QVariant();
}
