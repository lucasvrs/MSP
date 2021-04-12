#include "vokabeltrainer.h"
#include "ui_vokabeltrainer.h"
#include <QDebug>
#include <algorithm>

/*!
 * \brief Konstruktor
 * \param parent
 */
Vokabeltrainer::Vokabeltrainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vokabeltrainer)
{
    ui->setupUi(this);
    initiateGUI();
}
/*!
 * \brief Dekonstruktor
 */
Vokabeltrainer::~Vokabeltrainer()
{
    delete ui;
}
/*!
 * \brief shuffles the lists at random
 */
void Vokabeltrainer::shuffle()
{
    QList<Vokabel> call, trans;
    while(m_call.size() > 0)
    {
        int rand = qrand() % m_call.size();
        call.append(m_call.at(rand));
        m_call.removeAt(rand);
    }
    while(m_solution.size() > 0)
    {
        int rand = qrand() % m_solution.size();
        trans.append(m_solution.at(rand));
        m_solution.removeAt(rand);
    }
    m_call = call;
    m_solution = trans;

}
/*!
 * \brief increase the level
 * \param i level
 * \return true or false
 */
bool Vokabeltrainer::increaseLevel(int i)
{
    auto rand = qrand() % 100;
    switch(i){
    case(0):
        if(rand > 50) return true;
        return false;
    case(1):
        if(rand > 60) return true;
        return false;
    case(2):
        if(rand > 70) return true;
        return false;
    case(3):
        if(rand > 80) return true;
        return false;
    case(4):
        if(rand > 90) return true;
        return false;
    case(5):
        if(rand > 98) return true;
        return false;
    case(6):
        return false;
    }
    return false;
}
/*!
 * \brief initiate GUI. Connect buttons with methods
 */
void Vokabeltrainer::initiateGUI()
{
    m_conn.dbConnect();
    m_vokabeln = m_conn.readVokabeln();
    connect(ui->btn_start, SIGNAL(clicked()), this, SLOT(start()));
    connect(ui->btn_next, SIGNAL(clicked()), this, SLOT(next()));
    connect(ui->btn_solve, SIGNAL(clicked()), this, SLOT(solve()));
    m_subjects = m_conn.getSubjects();
    m_subjects = m_conn.getSubjects();
    for(QString string : m_subjects)
    {
        ui->cb_call->addItem(toCamelCase(string));
        ui->cb_solution->addItem(toCamelCase(string));
    }


}
/*!
 * \brief sets string to camelcase
 * \param string
 * \return string
 */
QString Vokabeltrainer::toCamelCase(const QString &s)
{
    QStringList cased;
           foreach (QString word, s.split(" ", QString::SkipEmptyParts))cased << word.at(0).toUpper() + word.mid(1);

           return cased.join(" ");
}
/*!
 * \brief is triggered by the solvebutton. Checks the solution
 */
void Vokabeltrainer::solve()
{
   if(ui->le__call->text() != "" && m_next){
    if(m_indexCall != m_call.size() && m_call.size() > 0)
    {
        if(ui->le_solution->text() == m_call.at(m_indexCall).translation)
        {
          ui->le_feedback->setText("Korrekt!");
          if(increaseLevel(m_call.at(m_indexCall).kastenLevel)){
                  Vokabel tempVokabel;
                  tempVokabel.vokabel = m_call.at(m_indexCall).vokabel;
                  tempVokabel.translation = m_call.at(m_indexCall).translation;
                  tempVokabel.kastenLevel = m_call.at(m_indexCall).kastenLevel+1;
                  tempVokabel.spracheVokabel = m_call.at(m_indexCall).spracheVokabel;
                  tempVokabel.spracheTranslation = m_call.at(m_indexCall).spracheTranslation;

                  m_conn.updateVokabel(m_call.at(m_indexCall).vokabelId,tempVokabel);
          }
        }
        else
        {
            QString string = "Falsche Antwort!";
            string += "  ";
            string += m_call.at(m_indexCall).translation;
            ui->le_feedback->setText(string);
        }
        m_indexCall++;
        m_next = false;
    }
    else if(m_indexSolution != m_solution.size() && m_solution.size() > 0)
    {
        if(ui->le_solution->text() == m_solution.at(m_indexSolution).vokabel)
        {
          ui->le_feedback->setText("Korrekt!");
          if(increaseLevel(m_solution.at(m_indexSolution).kastenLevel)){
                  Vokabel tempVokabel;
                  tempVokabel.vokabel = m_solution.at(m_indexSolution).vokabel;
                  tempVokabel.translation = m_solution.at(m_indexSolution).translation;
                  tempVokabel.kastenLevel = m_solution.at(m_indexSolution).kastenLevel+1;
                  tempVokabel.spracheVokabel = m_solution.at(m_indexSolution).spracheVokabel;
                  tempVokabel.spracheTranslation = m_solution.at(m_indexSolution).spracheTranslation;

                  m_conn.updateVokabel(m_solution.at(m_indexSolution).vokabelId,tempVokabel);
          }
        }
        else
        {
            QString string = "Falsche Antwort!";
            string += "  ";
            string += m_solution.at(m_indexSolution).vokabel;
            ui->le_feedback->setText(string);
        }
        m_indexSolution++;
        m_next = false;
    }
 }
}
/*!
 * \brief is triggered by the nextbutton. Shows new vocabulary
 */

void Vokabeltrainer::next()
{
    ui->le_feedback->setText("");
    ui->le_solution->setText("");
    ui->le__call->setText("");
    if(m_indexCall != m_call.size())
    {
       ui->le__call->setText(m_call.at(m_indexCall).vokabel);
       m_next = true;
    }
    else if(m_indexSolution != m_solution.size())
    {
      ui->le__call->setText(m_solution.at(m_indexSolution).translation);
      m_next = true;
    }
    else
    {
        ui->le_feedback->setText("Alle durch");
    }
}
/*!
 * \brief is triggered by the startbutton. Starts the coach
 */
void Vokabeltrainer::start()
{
    m_indexCall = 0;
    m_indexSolution = 0;
    m_call.clear();
    m_solution.clear();
    ui->le__call->clear();
    ui->le_feedback->clear();
    ui->le_solution->clear();

    for (int i = 0; i < m_vokabeln.length(); i++)
    {
     if(m_vokabeln.at(i).spracheVokabel == ui->cb_call->currentText().toLower() && m_vokabeln.at(i).spracheTranslation == ui->cb_solution->currentText().toLower())
     {
        m_call.append(m_vokabeln.at(i));
     }
     else if(m_vokabeln.at(i).spracheVokabel == ui->cb_solution->currentText().toLower() && m_vokabeln.at(i).spracheTranslation == ui->cb_call->currentText().toLower())
     {
         m_solution.append(m_vokabeln.at(i));
     }

    }
      shuffle();


    if(m_call.length() > 0)
    {
    ui->le__call->setText(m_call.at(m_indexCall).vokabel);
    auto i = m_call.at(m_indexCall).kastenLevel;
    ui->le_level->setText("Level: " + QString::number(i));
    }
    else if(m_solution.length() > 0)
    {
        ui->le__call->setText(m_solution.at(m_indexSolution).vokabel);
        auto j = m_call.at(m_indexSolution).kastenLevel;
        ui->le_level->setText("Level: " + QString::number(j));
    }
    m_next = true;
 }
