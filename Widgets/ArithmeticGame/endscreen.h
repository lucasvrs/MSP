#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <QDialog>
#include <QTextEdit>
#include "Txt/txtwriter.h"
#include "Txt/txtreader.h"

namespace Ui {
class endscreen;
}

class Endscreen : public QWidget
{
    Q_OBJECT

public:
    explicit Endscreen(QWidget *parent = nullptr, int score = 0, QPushButton *button = nullptr, QTextEdit *textedit =nullptr);
    ~Endscreen();

    bool fin() const;

private slots:
    void on_btn_back_clicked();

private:
    Ui::endscreen *ui;
    int score;
    bool m_fin = false;
    TXTWriter *m_ScoreWriter;
    TXTReader *m_ScoreReader;
    QVector<std::string> m_ScoreVector;
    QPushButton *m_backToMenuButton;
    QTextEdit *m_EndscoreTextEdit;

    void updateScore(int score);
};

#endif // ENDSCREEN_H
