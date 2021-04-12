#ifndef SUBJECTSTARTMENU_H
#define SUBJECTSTARTMENU_H

#include <QWidget>
#include "Widgets/Tiles/tileitem.h"

class QLabel;
class SideMenuTilesView;

class SubjectStartMenu : public QWidget
{
    Q_OBJECT
public:
    explicit SubjectStartMenu(QWidget *parent = nullptr);

private:
    QLabel* m_title;
    SideMenuTilesView* m_appMenu;

signals:
    void showWidget(QWidget* w);

public slots:
    void setTitle(const QString& title);
    void setPreviews(QList<TileItem*> previews);
};

#endif // SUBJECTSTARTMENU_H
