#ifndef DAYDETAILSGROUPBOX_H
#define DAYDETAILSGROUPBOX_H

#include <QGroupBox>

class QListWidget;
class QLineEdit;
class QPushButton;

class DayDetailsGroupBox : public QGroupBox
{
    Q_OBJECT

public:
    DayDetailsGroupBox(const QDate &date, QWidget* parent = nullptr);
    QStringList allAppointments();

private:
    QDate* m_date;
    QListWidget* m_listW;
    QLineEdit* m_nameEdit;
    QPushButton* m_colorBtn;
    QPushButton* m_saveBtn;
    QPushButton* m_cancelBtn;

signals:
    void needsUpdate(const QDate& date);

private slots:
    void addEntry(const QString& entry);
    void hideAll();
    void showAll();
};

#endif // DAYDETAILSGROUPBOX_H
