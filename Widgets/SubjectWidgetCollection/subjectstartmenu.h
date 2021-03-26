#ifndef SUBJECTSTARTMENU_H
#define SUBJECTSTARTMENU_H

#include <QWidget>

class QLabel;

class SubjectStartMenu : public QWidget
{
    Q_OBJECT
public:
    explicit SubjectStartMenu(QWidget *parent = nullptr);

private:
    QLabel* m_title;

signals:

public slots:
    void setTitle(const QString& title);
};

#endif // SUBJECTSTARTMENU_H
