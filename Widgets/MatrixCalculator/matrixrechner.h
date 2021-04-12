#ifndef MATRIXRECHNER_H
#define MATRIXRECHNER_H

#include <QDialog>
#include <QGridLayout>
#include "entryedit.h"
#include "Matrix.h"

namespace Ui {
class Matrixrechner;
}

class Matrixrechner : public QWidget
{
    Q_OBJECT

public:
    explicit Matrixrechner(QWidget *parent = nullptr, int rowa = 2, int cola = 2, int rowb = 2, int colb = 2);
    ~Matrixrechner();
    void updateResult();

    void updateMatrixA_bigger();
    void updateMatrixB_bigger();
    void updateMatrixA_smaller();
    void updateMatrixB_smaller();


    void addMatrix();
    void subMatrix();
    void multMatrix();
    void determinante(bool a);
    void rank(bool a);
    void mult(bool a);
    void powMat(bool a);

    void task();

    void trans(bool a);




private:
    Ui::Matrixrechner *ui;
    int rowa, cola, rowb, colb;
    static constexpr int m_maxRows = 10;
    static constexpr int m_maxCols = 10;


    QGridLayout* m_gridA;
    QGridLayout* m_gridB;
    QGridLayout* m_gridC;

    EntryEdit *m_matrixA[m_maxRows][m_maxCols];
    EntryEdit *m_matrixB[m_maxRows][m_maxCols];
    EntryEdit *m_matrixC[m_maxRows][m_maxCols];

    void initButton();
    void showMat();

    bool valid(QCharRef r);
};

#endif // MATRIXRECHNER_H
