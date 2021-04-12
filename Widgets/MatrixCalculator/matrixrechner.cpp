#include "matrixrechner.h"
#include "ui_matrixrechner.h"
/*!
 * \brief Constructor
 * \param parent
 * \param rowa number of rows of MatrixA
 * \param cola number of columns of MatrixA
 * \param rowb number of rows of MatrixB
 * \param colb number of colums of MatrixB
 */
Matrixrechner::Matrixrechner(QWidget *parent, int rowa, int cola, int rowb, int colb) :
    QWidget(parent),
    ui(new Ui::Matrixrechner)
  ,rowa(rowa)
  ,cola(cola)
  ,rowb(rowb)
  ,colb(colb)
{
    ui->setupUi(this);
    showMat();
    initButton();
}

/*!
 * \brief Deconstructor
 */
Matrixrechner::~Matrixrechner()
{
    delete ui;
}

void Matrixrechner::updateResult()
{

}
/*!
 * \brief increase size of MatrixA
 */
void Matrixrechner::updateMatrixA_bigger()
{
    msp::Matrix<double> mA(rowa,cola);
    for (int i = 0; i< rowa; i++ ) {

        for (int j = 0; j < cola ; j++ ) {
           if(m_matrixA[i][j]->text() != ""){ mA[i][j] = m_matrixA[i][j]->text().toInt();}
           else{ mA[i][j] = NULL;}
           m_matrixA[i][j]->hide();
        }

    }
    if(rowa < m_maxRows){
        rowa++;
        cola++;
    }
    for (int i = 0; i< rowa ; i++ ) {

        for (int j = 0; j < cola ; j++ ) {
            if(j< mA.columns() && i < mA.rows())
            {
            if(mA[i][j] == NULL)m_matrixA[i][j] = new EntryEdit();
            else m_matrixA[i][j] = new EntryEdit(QString::number(mA[i][j]));
            }
            else
            {
                m_matrixA[i][j] = new EntryEdit();

            }
            connect(m_matrixA[i][j], &EntryEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridA->addWidget(m_matrixA[i][j], i, j);



        }

    }
}
/*!
 * \brief increase size of MatrixB
 */
void Matrixrechner::updateMatrixB_bigger()
{
    msp::Matrix<double> mB(rowb,colb);

    for (int i = 0; i< rowb; i++ ) {

        for (int j = 0; j < colb ; j++ ) {

            if(m_matrixB[i][j]->text() != ""){ mB[i][j] = m_matrixB[i][j]->text().toInt();}
            else{ mB[i][j] = NULL;}
           m_matrixB[i][j]->hide();
        }

    }
    if(rowb < m_maxRows){
        rowb++;
        colb++;
    }

    for (int i = 0; i< rowb ; i++ ) {

        for (int j = 0; j < colb ; j++ ) {

            if(j< mB.columns() && i < mB.rows())
            {
                if(mB[i][j] == NULL) m_matrixB[i][j] = new EntryEdit();
                else m_matrixB[i][j] = new EntryEdit(QString::number(mB[i][j]));
            }
            else
            {
                m_matrixB[i][j] = new EntryEdit();

            }
            connect(m_matrixB[i][j], &EntryEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridB->addWidget(m_matrixB[i][j], i, j);
        }

    }

}
/*!
 * \brief decrease size of MatrixA
 */
void Matrixrechner::updateMatrixA_smaller()
{
    msp::Matrix<double> mA(rowa,cola);

    for (int i = 0; i< rowa ; i++ ) {

        for (int j = 0; j < cola ; j++ ) {

            if(m_matrixA[i][j]->text() != "") { mA[i][j] = m_matrixA[i][j]->text().toInt();}
            else{ mA[i][j] = NULL;}
            m_matrixA[i][j]->hide();



        }

    }
    if(rowa > 2)
    {
        rowa--;
        cola--;
    }

    for (int i = 0; i< rowa ; i++ ) {

        for (int j = 0; j < cola ; j++ ) {

            if(mA[i][j] == NULL) m_matrixA[i][j] = new EntryEdit();
            else m_matrixA[i][j] = new EntryEdit(QString::number(mA[i][j]));

            connect(m_matrixA[i][j], &QLineEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridA->addWidget(m_matrixA[i][j], i, j);



        }

    }
}
/*!
 * \brief decrease size of MatrixB
 */
void Matrixrechner::updateMatrixB_smaller()
{
    msp::Matrix<double> mB(rowb,colb);

    for (int i = 0; i< rowb ; i++ ) {

        for (int j = 0; j < colb ; j++ ) {

            if(m_matrixB[i][j]->text() != ""){ mB[i][j] = m_matrixB[i][j]->text().toInt();}
            else{ mB[i][j] = NULL;}
           m_matrixB[i][j]->hide();



        }

    }
    if(rowb > 2)
    {
        rowb--;
        colb--;
    }

    for (int i = 0; i< rowb ; i++ ) {

        for (int j = 0; j < colb ; j++ ) {

            if(mB[i][j] == NULL)m_matrixB[i][j] = new EntryEdit();
            else m_matrixB[i][j] = new EntryEdit(QString::number(mB[i][j]));
            connect(m_matrixB[i][j], &EntryEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridB->addWidget(m_matrixB[i][j], i, j);



        }

    }
}
/*!
 * \brief add MatrixA with MatrixB
 */
void Matrixrechner::addMatrix()
{
    int r = 0;
    int c = 0;

    for (int i = 0; i < rowa ;i++ ) {
        if(m_matrixA[i][0]) r++;
    }
    for (int j = 0; j < cola ;j++ ) {
      if(m_matrixA[1][j]->text() != "") c++;
    }

    msp::Matrix<double> mA(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mA[i][j] = m_matrixA[i][j]->text().toDouble();

        }
    }

     r = 0;
     c = 0;

    for (int i = 0; i < rowb ;i++ ) {
        if(m_matrixB[i][0]) r++;
    }

    for (int j = 0; j < colb ;j++ ) {
      if(m_matrixB[1][j]->text() != "") c++;
    }

    msp::Matrix<double> mB(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mB[i][j] = m_matrixB[i][j]->text().toDouble();

        }
    }
    if(c > 0){
   if(mA.rows() == mB.rows() && mB.columns() == mB.columns()){
    msp::Matrix<double> mC = mA + mB;
    qDebug() << mC;

    for (int i = 0; i< mC.rows() ; i++ ) {

        for (int j = 0; j < mC.columns() ; j++ ) {

            m_matrixC[i][j] = new EntryEdit(QString::number(mC[i][j]));

            connect(m_matrixC[i][j], &EntryEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridC->addWidget(m_matrixC[i][j], i, j);

        }

    }
    ui->le_error->clear();

   }
   else
   {
       ui->le_error->setText("A und B müssen gleich groß sein");

   }
}



}
/*!
 * \brief subtract MatrixA with MatrixB
 */
void Matrixrechner::subMatrix()
{
    int r = 0;
    int c = 0;

    for (int i = 0; i < rowa ;i++ ) {
        if(m_matrixA[i][0]) r++;
    }
    for (int j = 0; j < cola ;j++ ) {
      if(m_matrixA[1][j]->text() != "") c++;
    }

    msp::Matrix<double> mA(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mA[i][j] = m_matrixA[i][j]->text().toDouble();

        }
    }

     r = 0;
     c = 0;

    for (int i = 0; i < rowb ;i++ ) {
        if(m_matrixB[i][0]) r++;
    }

    for (int j = 0; j < colb ;j++ ) {
      if(m_matrixB[1][j]->text() != "") c++;
    }

    msp::Matrix<double> mB(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mB[i][j] = m_matrixB[i][j]->text().toDouble();

        }
    }
    if(c > 0){
   if(mA.rows() == mB.rows() && mB.rows() == mB.rows()){
    msp::Matrix<double> mC = mA - mB;
    qDebug() << mC;

    for (int i = 0; i< mC.rows() ; i++ ) {

        for (int j = 0; j < mC.columns() ; j++ ) {

            m_matrixC[i][j] = new EntryEdit(QString::number(mC[i][j]));

            connect(m_matrixC[i][j], &EntryEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridC->addWidget(m_matrixC[i][j], i, j);

        }

}
    ui->le_error->clear();

   }
   else
   {
       ui->le_error->setText("A und B müssen gleich groß sein");

   }
}

}
/*!
 * \brief multiplies MatrixA with MatrixB
 */

void Matrixrechner::multMatrix()
{
    int r = 0;
    int c = 0;

    for (int i = 0; i < rowa ;i++ ) {
        if(m_matrixA[i][0]) r++;
    }
    for (int j = 0; j < cola ;j++ ) {
      if(m_matrixA[1][j]->text() != "") c++;
    }

    msp::Matrix<double> mA(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mA[i][j] = m_matrixA[i][j]->text().toDouble();

        }
    }

     r = 0;
     c = 0;

    for (int i = 0; i < rowb ;i++ ) {
        if(m_matrixB[i][0]) r++;
    }

    for (int j = 0; j < colb ;j++ ) {
      if(m_matrixB[1][j]->text() != "") c++;
    }

    msp::Matrix<double> mB(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mB[i][j] = m_matrixB[i][j]->text().toDouble();

        }
    }

    if(c > 0){
    if(mA.columns() == mB.rows())
    {

    msp::Matrix<double> mC = mA * mB;

    for (int i = 0; i< mC.rows() ; i++ ) {

        for (int j = 0; j < mC.columns() ; j++ ) {

            m_matrixC[i][j] = new EntryEdit(QString::number(mC[i][j]));

            connect(m_matrixC[i][j], &EntryEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridC->addWidget(m_matrixC[i][j], i, j);

        }

    }
    ui->le_error->clear();
    }
    else
    {
      ui->le_error->setText("Spaltenanzahl von A muss gleich Reihenanzahl von B sein");
    }
    }
}
/*!
 * \brief calculate determinante
 * \param a if a true, it calculates from MatrixA
 */
void Matrixrechner::determinante(bool a)
{
    int r = 0;
    int c = 0;

    if(a){
    for (int i = 0; i < rowa ;i++ ) {
        if(m_matrixA[i][0]) r++;
    }
    for (int j = 0; j < cola ;j++ ) {
      if(m_matrixA[1][j]->text() != "") c++;
    }

    if(c != 0 )
    {
        msp::Matrix<double> mA(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mA[i][j] = m_matrixA[i][j]->text().toDouble();

        }
    }
  ui->le_detA->setText("Die Determinante beträgt: " + QString::number(msp::det(mA,mA.rows())));
    }
    }
    else
    {
        for (int i = 0; i < rowb ;i++ ) {
            if(m_matrixB[i][0]) r++;
        }
        for (int j = 0; j < colb ;j++ ) {
          if(m_matrixB[1][j]->text() != "") c++;
        }

        if(c != 0)
        {
            msp::Matrix<double> mB(r,c);
        for (int i = 0; i < r ;i++ ) {
            for (int j = 0; j < c ;j++ ) {
                  mB[i][j] = m_matrixB[i][j]->text().toDouble();

            }
        }
      ui->le_detB->setText("Die Determinante beträgt: " + QString::number(msp::det(mB,mB.rows())));

    }
    }
}
/*!
 * \brief calculate rank
 * \param a if a true, it calculates from MatrixA
 */
void Matrixrechner::rank(bool a)
{
    int r = 0;
    int c = 0;


    if(a){
    for (int i = 0; i < rowa ;i++ ) {
        if(m_matrixA[i][0]) r++;
    }
    for (int j = 0; j < cola ;j++ ) {
       if(m_matrixA[1][j]->text() != "") c++;
    }
    msp::Matrix<double> mA(r,c);
    if(mA.columns() > 0 && mA.rows() > 0){
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mA[i][j] = m_matrixA[i][j]->text().toDouble();

        }
    }
  ui->le_detA->setText("Der Rang beträgt: " + QString::number(msp::rank(mA)));
    }
    }
    else
    {
        for (int i = 0; i < rowb ;i++ ) {
            if(m_matrixB[i][0]) r++;
        }
        for (int j = 0; j < colb ;j++ ) {
          if(m_matrixB[1][j]->text() != "") c++;
        }

        msp::Matrix<double> mB(r,c);
        if(mB.rows() > 0 && mB.columns()>0){
        for (int i = 0; i < r ;i++ ) {
            for (int j = 0; j < c ;j++ ) {
                  mB[i][j] = m_matrixB[i][j]->text().toDouble();

            }
        }
      ui->le_detB->setText("Der Rang beträgt: " + QString::number(msp::rank(mB)));
        }
    }
}
/*!
 * \brief multiply a constant with matrix
 * \param a if a true, it calculates from MatrixA
 */
void Matrixrechner::mult(bool a)
{
    int r = 0;
    int c = 0;
if(a)
{
    for (int i = 0; i < rowa ;i++ ) {
        if(m_matrixA[i][0]) r++;
    }
    for (int j = 0; j < cola ;j++ ) {
      if(m_matrixA[1][j]->text() != "") c++;
    }

    if(c > 0){
    msp::Matrix<double> mA(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mA[i][j] = m_matrixA[i][j]->text().toDouble();

        }
    }
    mA = mA * ui->le_multiA->text().toDouble();

    for (int i = 0; i< mA.rows() ; i++ ) {

        for (int j = 0; j < mA.columns() ; j++ ) {

            m_matrixA[i][j] = new EntryEdit(QString::number(mA[i][j]));

            connect(m_matrixA[i][j], &EntryEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridA->addWidget(m_matrixA[i][j], i, j);

        }

    }
    }
}
else
{
    for (int i = 0; i < rowb ;i++ ) {
        if(m_matrixB[i][0]) r++;
    }
    for (int j = 0; j < colb ;j++ ) {
      if(m_matrixB[1][j]->text() != "") c++;
    }

    if(c > 0){
    msp::Matrix<double> mB(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mB[i][j] = m_matrixB[i][j]->text().toDouble();

        }
    }
    mB = mB * ui->le_multiB->text().toDouble();

    for (int i = 0; i< mB.rows() ; i++ ) {

        for (int j = 0; j < mB.columns() ; j++ ) {

            m_matrixB[i][j] = new EntryEdit(QString::number(mB[i][j]));

            connect(m_matrixB[i][j], &EntryEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridB->addWidget(m_matrixB[i][j], i, j);

        }

    }
    }

}
}
/*!
 * \brief pows matrix
 * \param a if a true, it calculates from MatrixA
 */
void Matrixrechner::powMat(bool a)
{
    int r = 0;
    int c = 0;
if(a)
{
    for (int i = 0; i < rowa ;i++ ) {
        if(m_matrixA[i][0]) r++;
    }
    for (int j = 0; j < cola ;j++ ) {
      if(m_matrixA[1][j]->text() != "") c++;
    }

    if(c > 0){
    msp::Matrix<double> mA(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mA[i][j] = m_matrixA[i][j]->text().toDouble();

        }
    }
    mA = mA^ui->le_powA->text().toDouble();

    for (int i = 0; i< mA.rows() ; i++ ) {

        for (int j = 0; j < mA.columns() ; j++ ) {

            m_matrixA[i][j] = new EntryEdit(QString::number(mA[i][j]));

            connect(m_matrixA[i][j], &EntryEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridA->addWidget(m_matrixA[i][j], i, j);

        }

    }
    }
}
else
{
    for (int i = 0; i < rowb ;i++ ) {
        if(m_matrixB[i][0]) r++;
    }
    for (int j = 0; j < colb ;j++ ) {
      if(m_matrixB[1][j]->text() != "") c++;
    }

    if(c > 0){
    msp::Matrix<double> mB(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mB[i][j] = m_matrixB[i][j]->text().toDouble();

        }
    }
    mB = mB^ui->le_powB->text().toDouble();

    for (int i = 0; i< mB.rows() ; i++ ) {

        for (int j = 0; j < mB.columns() ; j++ ) {

            m_matrixB[i][j] = new EntryEdit(QString::number(mB[i][j]));

            connect(m_matrixB[i][j], &EntryEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridB->addWidget(m_matrixB[i][j], i, j);

        }

    }
 }
}

}

void Matrixrechner::task()
{
    int r = 0;
    int c = 0;

    for (int i = 0; i < rowa ;i++ ) {
        if(m_matrixA[i][0]) r++;
    }
    for (int j = 0; j < cola ;j++ ) {
      if(m_matrixA[1][j]->text() != " ") c++;
    }

    msp::Matrix<double> mA(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mA[i][j] = m_matrixA[i][j]->text().toDouble();

        }
    }

     r = 0;
     c = 0;

    for (int i = 0; i < rowb ;i++ ) {
        if(m_matrixB[i][0]) r++;
    }

    for (int j = 0; j < colb ;j++ ) {
      if(m_matrixB[1][j]->text() != " ") c++;
    }

    msp::Matrix<double> mB(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mB[i][j] = m_matrixB[i][j]->text().toDouble();

        }
    }



}
/*!
 * \brief transposes matrix
 * \param a if a true, it calculates from MatrixA
 */
void Matrixrechner::trans(bool a)
{
    int r = 0;
    int c = 0;
if(a)
{
    for (int i = 0; i < rowa ;i++ ) {
        if(m_matrixA[i][0]) r++;
    }
    for (int j = 0; j < cola ;j++ ) {
      if(m_matrixA[1][j]->text() != "") c++;
    }

    if(c > 0){
    msp::Matrix<double> mA(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mA[i][j] = m_matrixA[i][j]->text().toDouble();

        }
    }

    mA = mA.transponed();

    for (int i = 0; i< mA.rows() ; i++ ) {

        for (int j = 0; j < mA.columns() ; j++ ) {

            m_matrixA[i][j] = new EntryEdit(QString::number(mA[i][j]));

            connect(m_matrixA[i][j], &EntryEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridA->addWidget(m_matrixA[i][j], i, j);

        }

    }
    }
}
else
{
    for (int i = 0; i < rowb ;i++ ) {
        if(m_matrixB[i][0]) r++;
    }
    for (int j = 0; j < colb ;j++ ) {
      if(m_matrixB[1][j]->text() != "") c++;
    }

    if(c > 0){
    msp::Matrix<double> mB(r,c);
    for (int i = 0; i < r ;i++ ) {
        for (int j = 0; j < c ;j++ ) {
              mB[i][j] = m_matrixB[i][j]->text().toDouble();

        }
    }
    mB = mB.transponed();

    for (int i = 0; i< mB.rows() ; i++ ) {

        for (int j = 0; j < mB.columns() ; j++ ) {

            m_matrixB[i][j] = new EntryEdit(QString::number(mB[i][j]));

            connect(m_matrixB[i][j], &EntryEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridB->addWidget(m_matrixB[i][j], i, j);

        }

    }
 }
}
}

/*!
 * \brief init buttons. Connect slot with signals
 */
void Matrixrechner::initButton()
{

    connect(ui->btn_MatAP, &QPushButton::clicked, [this](){
        updateMatrixA_bigger();
    });
    connect(ui->btn_MatAM, &QPushButton::clicked, [this](){
        updateMatrixA_smaller();
    });

    connect(ui->btn_MatBP, &QPushButton::clicked, [this](){
        updateMatrixB_bigger();
    });

    connect(ui->btn_MatBM, &QPushButton::clicked, [this](){
        updateMatrixB_smaller();
    });

    connect(ui->btn_APlusB, &QPushButton::clicked, [this](){
        addMatrix();
    });

    connect(ui->btn_AMinB, &QPushButton::clicked, [this](){
        subMatrix();
    });

    connect(ui->btn_AMalB, &QPushButton::clicked, [this](){
        multMatrix();
    });

    connect(ui->btn_detA, &QPushButton::clicked, [this](){
        determinante(true);
    });
    connect(ui->btn_detB, &QPushButton::clicked, [this](){
        determinante(false);
    });

   connect(ui->btn_mulitA, &QPushButton::clicked, [this](){
        mult(true);
    });

   connect(ui->btn_mulitB, &QPushButton::clicked, [this](){
        mult(false);
    });

   connect(ui->btn_powA, &QPushButton::clicked, [this](){
       powMat(true);
   });

   connect(ui->btn_powB, &QPushButton::clicked, [this](){
       powMat(false);
   });

   connect(ui->btn_rank, &QPushButton::clicked, [this](){
       rank(true);
   });

   connect(ui->btn_rankB, &QPushButton::clicked, [this](){
       rank(false);
   });

   connect(ui->btn_trans, &QPushButton::clicked, [this](){
       trans(true);
   });

   connect(ui->btn_transB, &QPushButton::clicked, [this](){
       trans(false);
   });

}
/*!
 * \brief shows matrix
 */
void Matrixrechner::showMat()
{
    m_gridA = new QGridLayout(ui->wid_matA);
    m_gridB = new QGridLayout(ui->wid_matB);
    m_gridC = new QGridLayout(ui->wid_matC);


    for (int i = 0; i< rowa ; i++ ) {

        for (int j = 0; j < cola ; j++ ) {

            m_matrixA[i][j] = new EntryEdit();

            connect(m_matrixA[i][j], &EntryEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridA->addWidget(m_matrixA[i][j], i, j);

        }

    }

    for (int i = 0; i< rowb ; i++ ) {

        for (int j = 0; j < colb ; j++ ) {

            m_matrixB[i][j] = new EntryEdit();

            connect(m_matrixB[i][j], &EntryEdit::editingFinished, this, &Matrixrechner::updateResult);
            m_gridB->addWidget(m_matrixB[i][j], i, j);

        }

    }

}

bool Matrixrechner::valid(QCharRef r)
{
    if(r == "A" || r == "B" || r == "*" || r == "+" || r == "-" || r == "^" || r == "[0-9]{0,3}") return true;
    return false;
}
