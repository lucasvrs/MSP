#ifndef TODO_H
#define TODO_H

#include <QAbstractTableModel>



class ToDo : public QAbstractTableModel
{
public:

    ToDo();

    void populateData(const QList<QString> &task_name,const QList<QString> &prio, const QList<QString> &date);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;



private:
    QList<QString> m_taskName;
    QList<QString> m_prio;
    QList<QString> m_date;
};

#endif // TODO_H
