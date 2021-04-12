#ifndef REGEXEDIT_H
#define REGEXEDIT_H

#include <QLineEdit>

class RegexEdit : public QLineEdit
{
    Q_OBJECT

public:
    RegexEdit(const QString &contents, QWidget *parent = nullptr);
    RegexEdit(QWidget *parent = nullptr);

public slots:
    void setRegex(const QString& regex);
};

#endif // REGEXEDIT_H
