#include "kopfrechnenspiel.h"
#include "ui_kopfrechnenspiel.h"
#include <QWidget>
#include <string>
#include <QTimer>
#include <QDebug>
#include <windows.h>
#include <QKeyEvent>
#include <QLineEdit>
#include "endscreen.h"


/*!
 * \brief Konstruktor
 * \param parent
 * \param bool addSub
 * \param bool divMult
 * \param int level
 */
KopfrechnenSpiel::KopfrechnenSpiel(QWidget *parent, bool addSub, bool divMult, int level, QPushButton *button, QTextEdit *te_score, QLineEdit *te_solution, QTextEdit *te_task, QTextEdit *te_time):
    QWidget(parent),
    ui(new Ui::KopfrechnenSpiel),
    m_addSub(addSub),
    m_divMult(divMult),
    m_level(level),
    m_button(button),
    m_te_score(te_score),
    m_te_task(te_task),
    m_te_time(te_time),
    m_te_solution(te_solution)
{
    m_solved = true;
    m_score = 0;
    initiateGUI();
    initiateTimer();
    playGame();
}
/*!
 * \brief initiates GUI
 */
void KopfrechnenSpiel::initiateGUI()
{
    m_te_score->setText(QString::number(m_score));
    m_te_time->setText(QString::number(m_time));

    connect(m_button, SIGNAL(clicked()), this, SLOT(btn_solveClicked()));

}


/*!
 * \brief initiates Timer
 */
void KopfrechnenSpiel::initiateTimer()
{
    m_timer_time = new QTimer(this);
    connect(m_timer_time, SIGNAL(timeout()), this, SLOT(decreaseTime()));
    m_timer_time->start(1000);


    m_timer_game = new QTimer(this);
    connect(m_timer_game, SIGNAL(timeout()), this, SLOT(playGame()));
    m_timer_game->start(100);


}
/*!
 * \brief Dekonstruktor
 */
KopfrechnenSpiel::~KopfrechnenSpiel()
{

    delete ui;
    m_timer_time->disconnect();
    m_timer_game->disconnect();


}

/*!
 * \brief shows Endscreen
 */
void KopfrechnenSpiel::showEndscreen()
{
    m_fin = true;
/**
    Endscreen *e = new Endscreen(nullptr, m_score);
    e->setModal(true);
    e->exec();
    this->close();
*/
}

/*!
 * \brief decrease Time. the time is up, the endscreen is shown
 */
void KopfrechnenSpiel::decreaseTime()
{

    m_time--;
    if(m_time < 0)
    {
        m_time = 0;
    }

    m_te_time->setText(QString::number(m_time));

    if(m_time == 0)
    {
        m_timer_game->disconnect();
        m_timer_time->disconnect();
       if(m_fin){
        showEndscreen();
       }

    }

}

/*!
 * \brief calls playLevel, with different values
 */
void KopfrechnenSpiel::playGame()
{

  switch(m_level){
    case(1):
      playLevel(2,20,0);
      break;
    case(2):
      playLevel(2,50,2);
      break;
    case(3):
      playLevel(3,100,3);
      break;
    case(4):
      playLevel(3,200,5);
      break;
    case(5):
      playLevel(3,500,10);
      break;

  }

}
/*!
 * \brief creates a random number between low and high
 * \param low lowest number
 * \param high highest number
 * \return random number
 */
int KopfrechnenSpiel::randomNumber(int low, int high)
{
  return qrand() % ((high + 1) - low) + low;
}

/*!
 * \brief checks entered solution if Enter-Key pressed
 * \param Key-event
 */
void KopfrechnenSpiel::keyPressEvent(QKeyEvent * event)
{

   if(event->key() == 16777220)
   {
       m_userSolution = m_te_solution->text().toInt();
       if(m_userSolution == m_taskSolution) m_solved = true;
   }
   m_te_solution->clear();

}

/*!
 * \brief checks entered solution if Solve-Button pressed
 */
void KopfrechnenSpiel::btn_solveClicked()
{
    QPalette palRed, palGreen;
    palRed.setColor(QPalette::Background, Qt::red);
    palGreen.setColor(QPalette::Background, Qt::green);

    m_userSolution = m_te_solution->text().toInt();
    if(m_userSolution == m_taskSolution)
    {
        m_solved = true;
        this->setPalette(palGreen);
        m_time += 5;
        m_te_time->setText(QString::number(m_time));
        m_score += 10;
        m_te_score->setText(QString::number(m_score));
    }
    else
    {
       this->setPalette(palRed);
        m_time -= 5;
        if(m_time < 0)
        {
            m_time = 0;
            m_te_time->setText(QString::number(m_time));
            m_timer_game->disconnect();
            m_timer_time->disconnect();
            showEndscreen();

        }
    }

    m_te_solution->clear();

}

int KopfrechnenSpiel::score() const
{
    return m_score;
}

bool KopfrechnenSpiel::fin() const
{
    return m_fin;
}



/*!
 * \brief Creates random math-task
 * \param range how many numbers maximum are created
 * \param high  highest number
 * \param multi highest number in multiplikation + 10
 */
void KopfrechnenSpiel::playLevel(int range,int high, int multi)
{
 if(m_solved){
  m_taskSolution = -999;
  m_task = "";
  if(m_addSub && !m_divMult)
  {
      for (auto i = 0; i < randomNumber(1,range); i++)
      {

        if(m_taskSolution == -999)
        {
        m_taskSolution = randomNumber(1,high);
        m_task += QString::number(m_taskSolution);
        }

        auto p = randomNumber(0,1);

        if(p == 0 || m_taskSolution == 0)
        {
          m_task += " + ";
          auto rand = randomNumber(1,high);
          m_taskSolution += rand;
          m_task += QString::number(rand);
        }
        else
        {

            if(m_taskSolution < high)
            {
                m_task += " - ";
                auto rand = randomNumber(1,m_taskSolution);
                m_taskSolution -= rand;
                m_task += QString::number(rand);

            }
            else
            {
                m_task += " - ";
                auto rand = randomNumber(1, high);
                m_taskSolution -= rand;
                m_task += QString::number(rand);

            }

        }

      }
     m_te_task->setText(m_task);
     m_solved = false;
  }
  else if(!m_addSub && m_divMult)
  {
      for (auto i = 0; i < randomNumber(1,range); i++)
      {

        if(m_taskSolution == -999)
        {
        m_taskSolution = randomNumber(1,10 + multi);
        m_task += QString::number(m_taskSolution);
        }

        auto p = randomNumber(0,1);

        if(p == 0 || m_taskSolution == 0)
        {
          m_task += " * ";
          auto rand = randomNumber(1,10);
          m_taskSolution *= rand;
          m_task += QString::number(rand);
        }
        else
        {
            auto rand = randomNumber(1,10 + multi);
            while(m_taskSolution % rand != 0)
            {
               rand = randomNumber(1,10);
            }
            m_task += " / ";
            m_taskSolution /= rand;
            m_task += QString::number(rand);

        }

      }
     m_te_task->setText(m_task);
     m_solved = false;

  }
  else if(m_addSub && m_divMult)
  {
      for (auto i = 0; i < randomNumber(1,range); i++)
      {

        if(m_taskSolution == -999)
        {
        m_taskSolution = randomNumber(1,high);
        m_task += QString::number(m_taskSolution);
        }

        auto s = randomNumber(0,1);

        if(s == 0){

        auto p = randomNumber(0,1);

        if(p == 0 || m_taskSolution == 0)
        {
          m_task += " + ";
          auto rand = randomNumber(1,high);
          m_taskSolution += rand;
          m_task += QString::number(rand);
        }
        else
        {

            if(m_taskSolution < high)
            {
                m_task += " - ";
                auto rand = randomNumber(1,m_taskSolution);
                m_taskSolution -= rand;
                m_task += QString::number(rand);

            }
            else
            {
                m_task += " - ";
                auto rand = randomNumber(1, high);
                m_taskSolution -= rand;
                m_task += QString::number(rand);

            }

        }

      }
      else {


            m_task += " * ";
            auto rand = randomNumber(1,10 + multi);
            m_taskSolution *= rand;
            m_task += QString::number(rand);
        }
      }
     m_te_task->setText(m_task);
     m_solved = false;

  }

 }
}


