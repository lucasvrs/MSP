#include "formelsammlung.h"
#include "ui_formelsammlung.h"
#include "QDebug"
#include <QDomDocument>
#include <QDomElement>
#include <QStringListModel>

Formelsammlung::Formelsammlung(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formelsammlung)
   ,read("./../FinalMsp/Widgets/FormulaCollection/Formel.xml")
{
    ui->setupUi(this);
    initiateLists();
    connect(ui->le_Search, &QLineEdit::textChanged, this, &Formelsammlung::search);

}

Formelsammlung::~Formelsammlung()
{
    delete ui;
}

void Formelsammlung::search()
{
  ui->listView->model()->removeRows(0, ui->listView->model()->rowCount());
  if(ui->le_Search->text() == "")
  {
    showAll();
  }
  else
  {
      for(const QDomElement &e : *read.allElemsUnderRoot())
      {

           for(const QDomElement &cE : *read.allElemsUnderElem(e))
              {
                  QString string;
                  QString search = ui->le_Search->text();

                  bool match = true;
                  for(int i = 0; i < search.length(); i++)
                  {
                      if(cE.attribute("name")[i] != search[i])
                      {
                          match = false;
                          break;
                      }
                  }
                     //regulärer Ausdruck
                  if(cE.tagName() == "formel" && match)
                  {
                      string = string + cE.attribute("name") + ": \n ";
                      string = string + cE.text();

                      ui->listView->model()->insertRow(ui->listView->model()->rowCount());
                      QModelIndex index = ui->listView->model()->index(ui->listView->model()->rowCount()-1,0);
                      ui->listView->model()->setData(index, string);
              }
                  }

      }
  }

}

void Formelsammlung::initiateLists()
{
    ui->listView ->setDragEnabled(false);
    ui->listView -> setAcceptDrops(false);
    ui->listView -> setDropIndicatorShown(false);
    ui->listView->setModel(new QStringListModel());

    showAll();

}

void Formelsammlung::showAll()
{
    for(const QDomElement &e : *read.allElemsUnderRoot())
    {

         for(const QDomElement &cE : *read.allElemsUnderElem(e))
            {
                QString string;
                if(cE.tagName() == "formel") string = string + cE.attribute("name") + ": \n ";
                    string = string + cE.text();

                    ui->listView->model()->insertRow(ui->listView->model()->rowCount());
                    QModelIndex index = ui->listView->model()->index(ui->listView->model()->rowCount()-1,0);
                    ui->listView->model()->setData(index, string);
            }

    }
}
