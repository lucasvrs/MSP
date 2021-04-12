#ifndef KOPFRECHNENSPIEL_H
#define KOPFRECHNENSPIEL_H

#include <QDialog>
#include "const.h"
#include <QTextEdit>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class KopfrechnenSpiel; }
QT_END_NAMESPACE

class KopfrechnenSpiel : public QWidget
{
    Q_OBJECT

public:
    explicit KopfrechnenSpiel(QWidget *parent = nullptr, bool addSub = true, bool divMult = true, int level = 1, QPushButton *button = nullptr,
                              QTextEdit *te_score = nullptr, QLineEdit *te_solution = nullptr, QTextEdit *te_task = nullptr, QTextEdit *te_time = nullptr);
    ~KopfrechnenSpiel();

    bool fin() const;

    int score() const;

public slots:

    void decreaseTime();
     void playGame();
     void keyPressEvent(QKeyEvent * event);
     void btn_solveClicked();

private:

  Ui::KopfrechnenSpiel *ui;
  bool m_addSub,m_divMult, m_solved, m_fin = false;
  int m_level, m_score, m_taskSolution, m_userSolution;
  int m_time = 60;
  QTimer *m_timer_time, *m_timer_game;
  QString m_task;
  QPushButton *m_button;
  QTextEdit *m_te_score, *m_te_task, *m_te_time;
  QLineEdit *m_te_solution;



  void playLevel(int range, int high, int multi);
  int randomNumber(int low, int high);
  void showEndscreen();
  void initiateGUI();
  void initiateTimer();

};
#endif // KOPFRECHNENSPIEL_H
