/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "mainviewwidget.h"
#include "homewidget.h"
#include "Widgets/Calendar/calendarwidget.h"
#include "Widgets/Tiles/previewtilesview.h"
#include "Widgets/SubjectWidgetCollection/subjectstartmenu.h"
#include "Widgets/ToDoList/todolist.h"
#include "Widgets/Tiles/tileitem.h"
#include "Widgets/Help/helpwidget.h"

MainViewWidget::MainViewWidget(QWidget *parent) : QStackedWidget(parent)
{
    //defines layout
    HomeWidget* home = new HomeWidget;
    ToDoList* todo = new ToDoList;
    QWidget* hw = new QWidget;
    CalendarWidget* calendar = new CalendarWidget;
    PreviewTilesView* more = new PreviewTilesView;
    HelpWidget* help = new HelpWidget;
    m_app = new QWidget;
    SubjectStartMenu* menu = new SubjectStartMenu;
    addWidget(home);
    addWidget(todo);
    addWidget(hw);
    addWidget(calendar);
    addWidget(more);
    addWidget(help);
    addWidget(m_app);
    addWidget(menu);

    //connects
    connect(menu, &SubjectStartMenu::showWidget, [this](QWidget* w)
    {
        this->removeWidget(m_app);
        m_app = w;
        this->insertWidget(6, m_app);
        setCurrentIndex(6);
    });
    connect(more, &PreviewTilesView::showWidget, [this](QWidget* w)
    {
        this->removeWidget(m_app);
        m_app = w;
        this->insertWidget(6, m_app);
        setCurrentIndex(6);
    });
    connect(home, &HomeWidget::showSubject, [this, menu](const QString& title, QList<TileItem*> list, int id)
    {
        emit newTitle(title);
        menu->setTitle(title);
        menu->setPreviews(list);
        menu->setId(id);
        setCurrentIndex(7);
    });
    connect(home, &HomeWidget::setPrevWidget, this, &MainViewWidget::setPrevWidget);
    connect(menu, &SubjectStartMenu::addTile, home, &HomeWidget::addTile);
}
