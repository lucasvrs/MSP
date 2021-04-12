#include "hexedit.h"
#include <QRegularExpressionValidator>

HexEdit::HexEdit(const QString &contents, QWidget *parent) :
    QLineEdit(contents, parent)
{
    setAlignment(Qt::AlignCenter);
    setRegex();
}

HexEdit::HexEdit(QWidget *parent) :
    QLineEdit(parent)
{
    setAlignment(Qt::AlignCenter);
    setRegex();
}

void HexEdit::setRegex()
{
    setValidator(new QRegularExpressionValidator(QRegularExpression("#[a-fA-F0-9]{6}")));
}
