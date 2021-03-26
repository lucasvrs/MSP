#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

class QComboBox;
class QSpinBox;

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    SearchDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

private:
    QComboBox* m_month;
    QDate* m_date;
    QSpinBox* m_day;
    QSpinBox* m_year;

protected:
    void closeEvent(QCloseEvent* e) override;

signals:
    void dateChanged(const QDate& date);
    void closed();

private slots:
    void fitToDate();
};

#endif // SEARCHDIALOG_H
