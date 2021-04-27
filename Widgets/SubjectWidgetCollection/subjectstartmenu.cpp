/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "subjectstartmenu.h"
#include "Widgets/Tiles/sidemenutilesview.h"
#include "Widgets/Tiles/tileitem.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>

SubjectStartMenu::SubjectStartMenu(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    m_title = new QLabel("Title");
    QLineEdit* searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText("Search...");
    QListWidget* list = new QListWidget;
    m_appMenu = new SideMenuTilesView;
    QSpacerItem* lSpacer = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* rSpacer = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QHBoxLayout* header = new QHBoxLayout;
    header->addItem(lSpacer);
    header->addWidget(m_title);
    header->addItem(rSpacer);
    QGridLayout* contentLayout = new QGridLayout;
    contentLayout->addWidget(searchEdit, 0, 0);
    contentLayout->addWidget(m_appMenu, 0, 1, 2, 1);
    contentLayout->addWidget(list, 1, 0);
    layout->addLayout(header);
    layout->addLayout(contentLayout);

    //connects
    connect(m_appMenu, &SideMenuTilesView::showWidget, this, &SubjectStartMenu::showWidget);
    connect(m_appMenu, &SideMenuTilesView::addTile, this, &SubjectStartMenu::addTile);
}

//SLOTS**********************************************************
void SubjectStartMenu::setTitle(const QString& title)
{
    m_title->setText(title);
    m_appMenu->setTitle(title);
}

void SubjectStartMenu::setPreviews(QList<TileItem*> previews)
{
    m_appMenu->setPreview(previews);
}

void SubjectStartMenu::setId(int id)
{
    m_appMenu->setId(id);
}
