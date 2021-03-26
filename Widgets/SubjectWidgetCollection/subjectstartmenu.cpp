#include "subjectstartmenu.h"
#include "relatedappssidemenu.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>

SubjectStartMenu::SubjectStartMenu(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    m_title = new QLabel("Überschrift");
    QLineEdit* searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText("Search...");
    QListWidget* list = new QListWidget;
    RelatedAppsSideMenu* appMenu = new RelatedAppsSideMenu;
    QSpacerItem* lSpacer = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* rSpacer = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QHBoxLayout* header = new QHBoxLayout;
    header->addItem(lSpacer);
    header->addWidget(m_title);
    header->addItem(rSpacer);
    QGridLayout* contentLayout = new QGridLayout;
    contentLayout->addWidget(searchEdit, 0, 0);
    contentLayout->addWidget(appMenu, 0, 1, 2, 1);
    contentLayout->addWidget(list, 1, 0);
    layout->addLayout(header);
    layout->addLayout(contentLayout);
}

//SLOTS**********************************************************
void SubjectStartMenu::setTitle(const QString& title)
{
    m_title->setText(title);
}
