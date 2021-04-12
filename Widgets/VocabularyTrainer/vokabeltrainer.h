#ifndef VOKABELTRAINER_H
#define VOKABELTRAINER_H

#include <QDialog>
#include "Sql/sqlconnector.h"

namespace Ui {
class Vokabeltrainer;
}

class Vokabeltrainer : public QWidget
{
    Q_OBJECT

public:
    explicit Vokabeltrainer(QWidget *parent = nullptr);
    ~Vokabeltrainer();
    void shuffle();
    bool increaseLevel(int i);
    void initiateGUI();
    QString toCamelCase(const QString& s);

private slots:
    void solve();
    void next();
    void start();

private:
    Ui::Vokabeltrainer *ui;
    SQLConnector m_conn;
    QList<Vokabel> m_vokabeln, m_call, m_solution;
    QList<QString> m_subjects;
    int m_indexCall, m_indexSolution;
    bool m_next = false;

};

#endif // VOKABELTRAINER_H
