#include "mainviewwidget.h"
#include "homewidget.h"
#include "Widgets/Calendar/calendarwidget.h"
#include "Widgets/Tiles/previewtilesview.h"
#include "Widgets/SubjectWidgetCollection/subjectstartmenu.h"

MainViewWidget::MainViewWidget(QWidget *parent) : QStackedWidget(parent)
{
    //defines layout
    HomeWidget* home = new HomeWidget;
    QWidget* todo = new QWidget;
    QWidget* hw = new QWidget;
    CalendarWidget* calendar = new CalendarWidget;
    PreviewTilesView* more = new PreviewTilesView;
    QWidget* help = new QWidget;
    QWidget* app = new QWidget;
    SubjectStartMenu* menu = new SubjectStartMenu;
    addWidget(home);
    addWidget(todo);
    addWidget(hw);
    addWidget(calendar);
    addWidget(more);
    addWidget(help);
    addWidget(app);
    addWidget(menu);

    //connects
    connect(more, &PreviewTilesView::showWidget, [this](QWidget* w)
    {
        removeWidget(widget(6));
        addWidget(w);
        setCurrentIndex(6);
        //connect(w, &);
    });
    connect(home, &HomeWidget::showSubject, [this, menu](const QString& title)
    {
        menu->setTitle(title);
        setCurrentIndex(7);
    });
}
