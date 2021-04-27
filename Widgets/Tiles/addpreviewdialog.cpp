#include "addpreviewdialog.h"
#include "addpreviewview.h"
#include "tileitem.h"
#include <QGridLayout>

AddPreviewDialog::AddPreviewDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f)
{
    setFixedSize(1000, 500);
    QGridLayout* layout = new QGridLayout(this);
    AddPreviewView* view = new AddPreviewView;
    layout->addWidget(view);
    connect(view, &AddPreviewView::addTile, [this](TileItem* tile)
    {
        emit addTile(tile);
        close();
    });
}

//EVENTS******************************************************************************************
void AddPreviewDialog::closeEvent(QCloseEvent* e)
{
    emit closed();
    QDialog::closeEvent(e);
}
