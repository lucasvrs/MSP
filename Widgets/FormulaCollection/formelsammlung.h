#ifndef FORMELSAMMLUNG_H
#define FORMELSAMMLUNG_H

#include <QDialog>
#include "Xml/xmlreader.h"

namespace Ui {
class Formelsammlung;
}

class Formelsammlung : public QWidget
{
    Q_OBJECT

public:
    Formelsammlung(QWidget *parent = nullptr);
    ~Formelsammlung();

public slots:

    void search();


private:
    Ui::Formelsammlung *ui;
    void initiateLists();
    void showAll();
    XMLReader read;
};

#endif // FORMELSAMMLUNG_H
