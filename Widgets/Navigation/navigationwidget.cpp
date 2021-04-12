#include "navigationwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QDebug>

NavigationWidget::NavigationWidget(QWidget *parent) : QWidget(parent), m_prevPagesIndex(0), m_noPrevUpdate(false)
{
    //defines layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    QHBoxLayout* easyNavLayout = new QHBoxLayout;
    easyNavLayout->setMargin(0);
    easyNavLayout->setSpacing(0);

    //Buttons
    m_homeBtn = new QPushButton("Home");
    m_toDoBtn = new QPushButton("ToDo");
    m_hwBtn = new QPushButton("HW");
    m_calBtn = new QPushButton("Cal");
    m_moreBtn = new QPushButton("More");
    m_helpBtn = new QPushButton("Help");
    m_prevBtn = new QPushButton("Prev");
    m_nextBtn = new QPushButton("Next");
    m_btns = new QButtonGroup;
    m_btns->addButton(m_homeBtn);
    m_btns->addButton(m_toDoBtn);
    m_btns->addButton(m_hwBtn);
    m_btns->addButton(m_calBtn);
    m_btns->addButton(m_moreBtn);
    m_btns->addButton(m_helpBtn);
    for(QAbstractButton* btn : m_btns->buttons())
    {
        btn->setObjectName("navbtn");
        btn->setFixedSize(120, 120);
        connect(btn, &QAbstractButton::clicked, [this, btn]()
        {
            QPushButton* pbtn = static_cast<QPushButton*>(btn);
            m_noPrevUpdate = false;
            highlightButton(pbtn);
            setDefault(pbtn);
        });
    }
    m_prevBtn->setFixedWidth(m_homeBtn->width()/2);
    m_nextBtn->setFixedWidth(m_homeBtn->width()/2);
    m_prevBtn->setDisabled(true);
    m_nextBtn->setDisabled(true);

    QSpacerItem* vSpacer = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

    //defines layout
    easyNavLayout->addWidget(m_prevBtn);
    easyNavLayout->addWidget(m_nextBtn);
    layout->addLayout(easyNavLayout);
    layout->addWidget(m_homeBtn);
    layout->addWidget(m_toDoBtn);
    layout->addWidget(m_hwBtn);
    layout->addWidget(m_calBtn);
    layout->addWidget(m_moreBtn);
    layout->addItem(vSpacer);
    layout->addWidget(m_helpBtn);

    //standard methods
    insertPageBtnConnects();
    highlightButton(m_homeBtn);
    setDefault(m_homeBtn);

    //connects
    connect(m_prevBtn, &QPushButton::clicked, this, &NavigationWidget::prevPage);
    connect(m_nextBtn, &QPushButton::clicked, this, &NavigationWidget::nextPage);
}

/*! Insert pages into a page to pushbutton assertion map
 * \brief NavigationWidget::insertPageBtnConnects
 */
void NavigationWidget::insertPageBtnConnects()
{
    m_pagesConnect.insert(std::pair<Page, QPushButton *>(Page(MSP::HomePage, "Subjects"), m_homeBtn));
    m_pagesConnect.insert(std::pair<Page, QPushButton *>(Page(MSP::ToDoPage, "To-do"), m_toDoBtn));
    m_pagesConnect.insert(std::pair<Page, QPushButton *>(Page(MSP::HomeworkPage, "Homework"), m_hwBtn));
    m_pagesConnect.insert(std::pair<Page, QPushButton *>(Page(MSP::CalendarPage, "Calendar"), m_calBtn));
    m_pagesConnect.insert(std::pair<Page, QPushButton *>(Page(MSP::MoreAppsPage, "More Apps"), m_moreBtn));
    m_pagesConnect.insert(std::pair<Page, QPushButton *>(Page(MSP::HelpPage, "Help"), m_helpBtn));
}

//SLOTS******************************************************************************
/*! Highlights passed button
 * \brief NavigationWidget::highlightButton
 * \param btn - QPushButton
 */
void NavigationWidget::highlightButton(QPushButton* btn)
{
    Page page(MSP::NoPage, "");
    for(auto pair : m_pagesConnect)
    {
        if(pair.second == btn)
        {
            page = pair.first;
            break;
        }
    }
    if(!m_noPrevUpdate) updatePrevPages(page);
    emit updateContent(page);
}

/*! Updates list of previous pages visited
 * \brief NavigationWidget::updatePrevPages
 * \param page - new page
 */
void NavigationWidget::updatePrevPages(Page page)
{
    m_prevBtn->setDisabled(false);
    if(page.page == MSP::HomePage)
    {
        m_prevPages.clear();
        m_prevPagesIndex = -1;
        m_prevBtn->setDisabled(true);
        m_nextBtn->setDisabled(true);
    }
    else
    {
        if(m_prevPagesIndex != m_prevPages.size() - 1)
        {
            for(size_t i = m_prevPages.size() - 1; i > m_prevPagesIndex; i--)
            {
                m_prevPages.pop_back();
            }
            m_nextBtn->setDisabled(true);
        }
    }
    if(m_prevPages.size() == 10)
    {
        std::vector<Page> ref;
        for(int i = 0; i < 10; i++)
        {
            if(i == 0) continue;
            ref.push_back(m_prevPages[i]);
        }
    }
    m_prevPages.push_back(page);
    m_prevPagesIndex++;
    if(m_prevPagesIndex >= 2 && page.page == m_prevPages[m_prevPages.size() - 2].page)
    {
        m_prevPagesIndex--;
        m_prevPages.pop_back();
    }
}

/*! Sets style of all buttons to default except for the one passed
 * \brief NavigationWidget::setDefault
 * \param btn - QPushButton
 */
void NavigationWidget::setDefault(QPushButton* btn)
{
    for(QAbstractButton* oBtn : m_btns->buttons())
    {
        (oBtn == btn) ? btn->setDefault(true) : static_cast<QPushButton*>(oBtn)->setDefault(false);
    }
}

/*! Sets contents to the previous page
 * \brief NavigationWidget::prevPage
 */
void NavigationWidget::prevPage()
{
    m_noPrevUpdate = true;
    m_prevPagesIndex--;
    Page page = m_prevPages[m_prevPagesIndex];
    if(m_pagesConnect.count(page) != 0)
    {
        QPushButton* btn = m_pagesConnect.find(page)->second;
        highlightButton(btn);
        setDefault(btn);
    }
    if(m_prevPagesIndex == 0)
    {
        m_prevBtn->setDisabled(true);
    }
    m_nextBtn->setDisabled(false);
    emit updateContent(page);
}

/*! Sets contents to the page visited after the current
 * \brief NavigationWidget::nextPage
 */
void NavigationWidget::nextPage()
{
    m_noPrevUpdate = true;
    m_prevPagesIndex++;
    Page page = m_prevPages[m_prevPagesIndex];
    if(m_pagesConnect.count(page) != 0)
    {
        QPushButton* btn = m_pagesConnect.find(page)->second;
        highlightButton(btn);
        setDefault(btn);
    }
    if(m_prevPagesIndex == m_prevPages.size() - 1)
    {
        m_nextBtn->setDisabled(true);
    }
    m_prevBtn->setDisabled(false);
    emit updateContent(page);
}
