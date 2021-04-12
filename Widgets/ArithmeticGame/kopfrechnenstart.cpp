#include "kopfrechnenstart.h"
#include "ui_kopfrechnenstart.h"
#include "kopfrechnenspiel.h"
#include <QDebug>
#include "scorechart.h"

KopfrechnenStart::KopfrechnenStart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KopfrechnenStart)
{
    ui->setupUi(this);
    initiateGUI();


}

KopfrechnenStart::~KopfrechnenStart()
{
    delete ui;
}
/*!
 * \brief set the default values
 */
void KopfrechnenStart::setDefaultValue()
{
    m_addSub = false;
    m_divMult = false;
    m_levelIndex = 1;

}

/*!
 * \brief initiates GUI, sets color and connect Signals with Slots
 */
void KopfrechnenStart::initiateGUI()
{
    ui->setupUi(this);
    ui->stackedWidget_backgroundPage1->setFixedSize(500,500);
    ui->comb_Level->setCurrentIndex(1);
    ui->errorLabel->setStyleSheet(""
                                  "QLabel{"
                                  " background-color: rgba(0, 0, 0, 0);"
                                  "}"
                                  "");


    ui->cB_AddSub->connect(ui->cB_AddSub,   SIGNAL(clicked(bool)), this,  SLOT(cB_AddChecked(bool)));
    ui->cB_MultDiv->connect(ui->cB_MultDiv, SIGNAL(clicked(bool)), this,  SLOT(cB_MultChecked(bool)));
    connect(ui->comb_Level, &QComboBox::currentTextChanged, [this](QString level){
        levelBox(level);
        ui->errorLabel->setFocus();
    });
    ui->bt_start->connect(ui->bt_start, SIGNAL(clicked()), this, SLOT(btn_startClicked()));
    ui->bt_score->connect(ui->bt_score, SIGNAL(clicked()), this, SLOT(btn_scoreClicked()));
    ui->btn_btM->connect(ui->btn_btM, SIGNAL(clicked()), this, SLOT(btn_btMClicked()));
    ui->comb_Level->setCurrentIndex(0);
}


/*!
 * \brief sets m_addSub true, if selected
 * \param bool whether checkbox activated
 */
void KopfrechnenStart::cB_AddChecked(bool check)
{
  if (check)
  {
      m_addSub = true;
  }
  else
  {
      m_addSub = false;
  }

}
/*!
 * \brief sets m_divMult true, if selected
 * \param bool whether checkbox activated
*/
void KopfrechnenStart::cB_MultChecked(bool check)
{
    if (check)
    {
        m_divMult = true;
    }else
    {
        m_divMult = false;
    }

}

/*!
 * \brief checks selection of the comboBox and change the value of m_levelIndex
 * \param index selection of comboBox
 */
void KopfrechnenStart::levelBox(QString index)
{

    if(index == "Level 1")
    {
      m_levelIndex = 1;
    }
    else if(index == "Level 2")
    {
        m_levelIndex = 2;
    }
    else if(index == "Level 3")
    {
        m_levelIndex = 3;
    }
    else if(index == "Level 4")
    {
        m_levelIndex = 4;
    }
    else if(index == "Level 5")
    {
        m_levelIndex = 5;
    }
}

/*!
 * \brief m_addSub-Getter
 * \return bool m_addSub
 */
bool KopfrechnenStart::getAddSub() {return m_addSub;}

/*!
 * \brief m_divMult-Getter
 * \return bool m_divMult
 */
bool KopfrechnenStart::getDivMult() {return m_divMult;}

/*!
 * \brief m_levelIndex-Getter
 * \return int m_levelIndex
 */
int KopfrechnenStart::getLevelIndex(){return m_levelIndex;}

/*!
 * \brief Starts game
 */
void KopfrechnenStart::btn_startClicked()
{


if(!m_addSub && !m_divMult)
{
  ui->errorLabel->setText("Please take a selection");
}
else
{

spiel = new KopfrechnenSpiel(nullptr ,this->getAddSub(),this->getDivMult(), this->getLevelIndex(), ui->btn_solution, ui->te_score, ui->te_solution, ui->te_task, ui->te_time);

ui->stackedWidget_background->setCurrentIndex(2);

m_timer_time = new QTimer(this);
connect(m_timer_time, SIGNAL(timeout()), this, SLOT(checkBoolGame()));
m_timer_time->start(1);




}
}

/*!
 * \brief shows Score-History
 */
void KopfrechnenStart::btn_scoreClicked()
{
    ScoreChart *g = new ScoreChart();
    ui->gridLayout_score->addWidget(g->getChartView());
    ui->stackedWidget_background->setCurrentIndex(1);
}

void KopfrechnenStart::btn_btMClicked()
{
   ui->stackedWidget_background->setCurrentIndex(0);
}

void KopfrechnenStart::checkBoolGame()
{
  if(spiel->fin())
  {
    ui->stackedWidget_background->setCurrentIndex(3);
    m_timer_time->disconnect();
    end = new Endscreen(nullptr,spiel->score(), ui->btn_back_end, ui->te_score_end);
    spiel->~KopfrechnenSpiel();
    connect(m_timer_time, SIGNAL(timeout()), this, SLOT(checkBoolEnd()));
    m_timer_time->start(1);

  }

}

void KopfrechnenStart::checkBoolEnd()
{
   if(end->fin())
   {
       ui->stackedWidget_background->setCurrentIndex(0);
       m_timer_time->disconnect();
       end->~Endscreen();
   }

}
