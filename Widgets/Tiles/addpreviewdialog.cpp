#include "addpreviewdialog.h"
#include "addpreviewview.h"
#include <QGridLayout>

AddPreviewDialog::AddPreviewDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f)
{
    QGridLayout* layout = new QGridLayout(this);
    AddPreviewView* view = new AddPreviewView;
    layout->addWidget(view);
}

//EVENTS******************************************************************************************
void AddPreviewDialog::closeEvent(QCloseEvent* e)
{
    emit closed();
    QDialog::closeEvent(e);
}
