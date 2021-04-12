#include "createcollectiondialog.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QColorDialog>
#include <QRegExpValidator>
#include "tilefactory.h"

CreateCollectionDialog::CreateCollectionDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    m_color(Qt::black),
    m_textColor(Qt::white)
{
    setWindowTitle("Create Collection");

    QGridLayout* layout = new QGridLayout(this);
    QLabel* headerLabel = new QLabel("Create Collection");
    headerLabel->setAlignment(Qt::AlignCenter);
    QLabel* nameLabel = new QLabel("Name:");
    QLineEdit* nameEdit = new QLineEdit;
    nameEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z ]{1,}")));
    QLabel* colorLabel = new QLabel("Color:");
    m_colorBtn = new QPushButton;
    m_colorBtn->setObjectName("createColColorBtn");
    QLabel* textColorLabel = new QLabel("Text color:");
    m_textColorBtn = new QPushButton();
    m_textColorBtn->setObjectName("createColTextColorBtn");

    QHBoxLayout* footerLayout = new QHBoxLayout;
    QSpacerItem* hFooterSpacerL = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QPushButton* cancelBtn = new QPushButton("Cancel");
    QPushButton* createBtn = new QPushButton("Create");
    footerLayout->addItem(hFooterSpacerL);
    footerLayout->addWidget(cancelBtn);
    footerLayout->addWidget(createBtn);

    layout->addWidget(headerLabel, 0, 0, 1, 3);
    layout->addWidget(nameLabel, 1, 0, 1, 1);
    layout->addWidget(nameEdit, 1, 1, 1, 2);
    layout->addWidget(colorLabel, 2, 0, 1, 1);
    layout->addWidget(m_colorBtn, 2, 1, 1, 1);
    layout->addWidget(textColorLabel, 3, 0, 1, 1);
    layout->addWidget(m_textColorBtn, 3, 1, 1, 1);
    layout->addLayout(footerLayout, 4, 0, 1, 3);

    connect(m_colorBtn, &QPushButton::clicked, this, &CreateCollectionDialog::getColor);
    connect(m_textColorBtn, &QPushButton::clicked, this, &CreateCollectionDialog::getTextColor);
    connect(cancelBtn, &QPushButton::clicked, this, &CreateCollectionDialog::close);
    connect(createBtn, &QPushButton::clicked, [this, nameEdit]()
    {
        QString text = nameEdit->text();
        if(text != "+" && text != "")
        {
            createTile(text, m_color, m_textColor);
            close();
        }
    });
}

//EVENTS******************************************************************************************
void CreateCollectionDialog::closeEvent(QCloseEvent* e)
{
    emit closed();
    QDialog::closeEvent(e);
}

//SLOTS*************************************************************************************
void CreateCollectionDialog::createTile(const QString& text, const QColor& color, const QColor& textColor)
{
    TileFactory fac;
    fac.createTile(text, color, textColor);
    emit newTile();
}

void CreateCollectionDialog::getColor()
{
    m_color = QColorDialog::getColor();
    m_colorBtn->setStyleSheet("#createColColorBtn{background-color: rgba("
                              "" + QString::number(m_color.red()) +
                              ", " + QString::number(m_color.green()) +
                              ", " + QString::number(m_color.blue()) +
                              ", 255)}");
}

void CreateCollectionDialog::getTextColor()
{
    m_textColor = QColorDialog::getColor();
    m_textColorBtn->setStyleSheet("#createColTextColorBtn{background-color: rgba("
                              "" + QString::number(m_textColor.red()) +
                              ", " + QString::number(m_textColor.green()) +
                              ", " + QString::number(m_textColor.blue()) +
                              ", 255)}");
}
