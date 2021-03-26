#include "relatedappssidemenu.h"
#include <QVBoxLayout>

RelatedAppsSideMenu::RelatedAppsSideMenu(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    for(int i = 0; i < 4; i++)
    {
//        AppPreview* app = new AppPreview("Taschenrechner");
//        layout->addWidget(app);
    }
}
