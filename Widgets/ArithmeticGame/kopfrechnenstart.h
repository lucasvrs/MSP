#ifndef KOPFRECHNENSTART_H
#define KOPFRECHNENSTART_H

#include <QDialog>
#include <QTimer>
#include "kopfrechnenspiel.h"
#include "endscreen.h"

namespace Ui {
class KopfrechnenStart;
}

class KopfrechnenStart : public QWidget
{
    Q_OBJECT

public:
    KopfrechnenStart(QWidget *parent = nullptr);
    ~KopfrechnenStart();
    bool getAddSub();
    bool getDivMult();
    int getLevelIndex();

public slots:

     void cB_AddChecked(bool check);
     void cB_MultChecked(bool check);
     void levelBox(QString index);
     void btn_startClicked();
     void btn_scoreClicked();
     void btn_btMClicked();
     void checkBoolGame();
     void checkBoolEnd();




private:



    Ui::KopfrechnenStart *ui;
    KopfrechnenSpiel *spiel ;
    Endscreen *end;
    bool m_addSub, m_divMult;
    int m_countdown, m_score, m_solution, m_levelIndex;
    QTimer *m_timer_time;

    void initiateGUI();
    void setDefaultValue();
    bool getCheck();

};

#endif // KOPFRECHNENSTART_H
