#include "entryedit.h"
#include <QRegExpValidator>

EntryEdit::EntryEdit(QWidget* parent) :
    QLineEdit(parent)
{
    init();
}

EntryEdit::EntryEdit(const QString& contents, QWidget* parent) :
    QLineEdit(contents, parent)
{
    init();
}

void EntryEdit::init()
{
    setAlignment(Qt::AlignCenter);
    setPlaceholderText(" ");
    setValidator(new QRegExpValidator(QRegExp("[0-9]{0,3}")));
}
