/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Widgets/mspwidget.h"
#include "Utils/loader.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Bildungssoftware");
    setStyleSheet(readStylesheet("./../FinalMsp/Styling/lightmode.qss"));

    QVBoxLayout* layout = new QVBoxLayout(ui->centralwidget);
    layout->setMargin(0);
    layout->setSpacing(0);
    MspWidget* msp = new MspWidget;
    layout->addWidget(msp);

    //connects
    connect(msp, &MspWidget::changeStyle, [this](int mode)
    {
        switch(mode)
        {
        case 0:
            setStyleSheet(readStylesheet("./../FinalMsp/Styling/lightmode.qss"));
            break;
        case 1:
            setStyleSheet(readStylesheet("./../FinalMsp/Styling/darkmode.qss"));
            break;
        default:
            setStyleSheet(readStylesheet("./../FinalMsp/Styling/lightmode.qss"));
            break;
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

