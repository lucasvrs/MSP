#include "homewidget.h"
#include "Widgets/Tiles/tilesview.h"
#include <QVBoxLayout>

HomeWidget::HomeWidget(QWidget *parent) : QWidget(parent)
{
    //defines layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    TilesView* view = new TilesView;
    layout->addWidget(view);

    //connects
    connect(view, &TilesView::showSubject, this, &HomeWidget::showSubject);
}
