#ifndef REACTION_H
#define REACTION_H

#include <QDialog>
#include <QTime>

namespace Ui {
class Reaction;
}

class Reaction : public QWidget
{
    Q_OBJECT

public:
    explicit Reaction(QWidget *parent = nullptr);
    ~Reaction();


public slots:
      void keyPressEvent(QKeyEvent * event);
      void startTimer();
      void startButtonPressed();


private:
    Ui::Reaction *ui;
    QPalette m_palRed, m_palGreen;
    bool m_ready = false;
    int m_rand;
    int m_timer = 0;
    QTimer* m_timer_game;
    QTime m_time;

    void randomReaction();
    void givegreenLight();
};

#endif // REACTION_H
