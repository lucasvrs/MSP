#include "regexedit.h"
#include <QRegularExpressionValidator>

RegexEdit::RegexEdit(const QString &contents, QWidget *parent) :
    QLineEdit(contents, parent)
{
    setAlignment(Qt::AlignCenter);
}

RegexEdit::RegexEdit(QWidget *parent) :
    QLineEdit(parent)
{
    setAlignment(Qt::AlignCenter);
}

void RegexEdit::setRegex(const QString& regex)
{
    setValidator(new QRegularExpressionValidator(QRegularExpression(regex)));
}
