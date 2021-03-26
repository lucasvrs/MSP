#ifndef NAVIGATIONWIDGET_H
#define NAVIGATIONWIDGET_H

#include "Utils/msp.h"
#include <QWidget>

class QPushButton;
class QButtonGroup;

class NavigationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NavigationWidget(QWidget *parent = nullptr);

private:
    QButtonGroup* m_btns;
    QPushButton* m_homeBtn;
    QPushButton* m_toDoBtn;
    QPushButton* m_hwBtn;
    QPushButton* m_calBtn;
    QPushButton* m_moreBtn;
    QPushButton* m_helpBtn;
    QPushButton* m_prevBtn;
    QPushButton* m_nextBtn;
    std::map<Page, QPushButton*> m_pagesConnect;
    std::vector<Page> m_prevPages;
    unsigned long m_prevPagesIndex;
    void insertPageBtnConnects();
    bool m_noPrevUpdate;

signals:
    void updateContent(Page page);

private slots:
    void highlightButton(QPushButton *btn);
    void updatePrevPages(Page page);
    void setDefault(QPushButton* btn);
    void prevPage();
    void nextPage();
};

#endif // NAVIGATIONWIDGET_H
