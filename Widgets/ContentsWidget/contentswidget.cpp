#include "contentswidget.h"
#include "headerwidget.h"
#include "mainviewwidget.h"
#include "Widgets/Navigation/navigationwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

ContentsWidget::ContentsWidget(QWidget *parent) : QWidget(parent)
{
    //defines layout
    QHBoxLayout* layout = new QHBoxLayout(this);
    QVBoxLayout* contentsLayout = new QVBoxLayout;
    NavigationWidget* nav = new NavigationWidget;
    HeaderWidget* header = new HeaderWidget;
    MainViewWidget* main = new MainViewWidget;
    layout->addWidget(nav);
    contentsLayout->addWidget(header);
    contentsLayout->addWidget(main);
    layout->addLayout(contentsLayout);

    //connects
    connect(nav, &NavigationWidget::updateContent, [main, header](Page page)
    {
        main->setCurrentIndex(page.page);
        header->setHeader(page.title);
    });
}
