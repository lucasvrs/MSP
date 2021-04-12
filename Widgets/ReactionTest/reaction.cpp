#include "reaction.h"
#include "ui_reaction.h"
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
/*!
 * \brief Konstruktor
 * \param parent QWidget
 */
Reaction::Reaction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Reaction)
{
    ui->setupUi(this);
    ui->background_widget->setFixedSize(500,500);

    ui->te_text->setObjectName("reactionStart");

    connect(ui->button, SIGNAL(clicked()), this, SLOT(startButtonPressed()));

}
/*!
 * \brief Dekonstruktor
 */
Reaction::~Reaction()
{
    delete ui;
}

/*!
 * \brief stops time, if Enter-key pressed
 * \param event key-event
 */
void Reaction::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == 16777220 && m_ready)
   {
        QPalette p = ui->te_text->palette();
        p.setColor(QPalette::Base, Qt::blue);
        ui->te_text->setPalette(p);
        m_palGreen.setColor(QPalette::Background, Qt::blue);
        this->setPalette(m_palGreen);
        auto timeElapsed = m_time.elapsed()/1000.0;
        ui->te_text->setText(QString::number(timeElapsed));
        m_ready = false;
        m_timer_game->~QTimer();
        ui->button->show();
   }
}

/*!
 * \brief creates random number and call startTimer
 */
void Reaction::randomReaction()
{
   m_rand = qrand() % ((5697 + 1) - 1200) + 1200;
   m_timer_game = new QTimer(this);
   connect(m_timer_game, SIGNAL(timeout()), this, SLOT(startTimer()));
   m_timer_game->start(1);

}

/*!
 * \brief starts Timer
 */
void Reaction::startTimer()
{
    m_timer++;
    if(m_timer == m_rand)
    {
      givegreenLight();
      m_timer_game->disconnect();
    }

}

void Reaction::startButtonPressed()
{
    this->setPalette(m_palRed);
    ui->te_text->setText("WAIT FOR GREEN");
    QFont f = ui->te_text->font();
    f.setPointSize(28);
    ui->te_text->setFont(f);
    ui->te_text->setObjectName("reactionRed");
    ui->button->hide();
    randomReaction();

}

/*!
 * \brief change Background green
 */
void Reaction::givegreenLight()
{
    ui->te_text->setObjectName("reactionGreen");
    m_ready = true;
    ui->te_text->setText("GO");
    m_time.start();

}
