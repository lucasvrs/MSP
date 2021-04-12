#include "endscreen.h"
#include "ui_endscreen.h"
#include <QDir>
#include <stdio.h>

/*!
 * \brief Konstruktor
 * \param parent QWidget
 * \param score achieved score
 */
Endscreen::Endscreen(QWidget *parent, int score,QPushButton *button, QTextEdit *textedit) :
    QWidget(parent),
    ui(new Ui::endscreen),
    score(score),
    m_backToMenuButton(button),
    m_EndscoreTextEdit(textedit)
{

    m_EndscoreTextEdit->setText("Endscore: " + QString::number(score));
    updateScore(score);
    connect(m_backToMenuButton, SIGNAL(clicked()), this, SLOT(on_btn_back_clicked()));



}
/*!
 * \brief Dekonstruktor
 */
Endscreen::~Endscreen()
{
    delete ui;
}


/*!
 * \brief closed Window
 */
void Endscreen::on_btn_back_clicked()
{
      m_fin = true;
}

bool Endscreen::fin() const
{
    return m_fin;
}

/*!
 * \brief Updates the ScoreFile
 * \param score reached score
 */
void Endscreen::updateScore(int score)
{

    m_ScoreReader = new TXTReader();
    m_ScoreWriter = new TXTWriter();
    QString path = QDir().absolutePath() + "/../Kopfrechnen" + "/KopfrechnenScore";
    m_ScoreVector = m_ScoreReader->getInput(path.toUtf8().constData());
    std::string newScore;

    if(m_ScoreVector.length() == 5)
    {
       newScore.append(m_ScoreVector.at(1) + "\n");
       newScore.append(m_ScoreVector.at(2) + "\n");
       newScore.append(m_ScoreVector.at(3) + "\n");
       newScore.append(m_ScoreVector.at(4) +  "\n");
       newScore.append(QString::number(score).toUtf8().constData());
       m_ScoreWriter->writeInFile(path.toUtf8().constData(), newScore);
    }
    else
    {
        m_ScoreWriter->writeInFileAppend(path.toUtf8().constData(),"\n");
        m_ScoreWriter->writeInFileAppend(path.toUtf8().constData(),QString::number(score).toUtf8().constData() );

    }




}
