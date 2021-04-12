#ifndef HEXEDIT_H
#define HEXEDIT_H

#include <QLineEdit>

class HexEdit : public QLineEdit
{
    Q_OBJECT

public:
    HexEdit(const QString &contents, QWidget *parent = nullptr);
    HexEdit(QWidget *parent = nullptr);

private:
    void setRegex();
};

#endif // HEXEDIT_H
