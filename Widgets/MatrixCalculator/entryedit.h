#ifndef ENTRYEDIT_H
#define ENTRYEDIT_H

#include <QLineEdit>

class EntryEdit : public QLineEdit
{
    Q_OBJECT

public:
    EntryEdit(QWidget* parent = nullptr);
    EntryEdit(const QString& contents, QWidget* parent = nullptr);
    void init();
};

#endif // ENTRYEDIT_H
