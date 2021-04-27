#include "mainhelpcontentswidget.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include "helpwidgetfactory.h"
#include <QDebug>
#include <QGraphicsItem>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QTextEdit>
/*!
 * \brief Constructor
 * \param parent
 */
MainHelpContentsWidget::MainHelpContentsWidget(QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    label = new QLabel;
    labelText = new QTextEdit;
    labelText->setReadOnly(true);
    label->setText("Documentation");
    label->setAlignment(Qt::AlignCenter);
    labelText->setAlignment(Qt::AlignLeft);
    labelText->setText("This project represents an ordered and easy to use collection of modules in order to manage everyday life. "
                       "The modules can cover any imaginable topic and are managed within this software. "
                       "The following documentation offers a description of every standard module with its functionality and its shortcuts, "
                       "just to make everything as comfortable and easy to understand for you as we can!");
    m_layout->addWidget(label);
    m_layout->addWidget(labelText);

    HelpWidgetFactory *fac = new HelpWidgetFactory();
    m_list = fac->widgets();

    addWidgets(m_list);

    m_layout->setSpacing(1);
}
/*!
 * \brief add WisgetItems to layout
 * \param list list of WidgetItems
 */
void MainHelpContentsWidget::addWidgets(QList<WidgetItem*> list)
{
    gridLayout = new QGridLayout();
    m_layout->addLayout(gridLayout);

    int row = 2;

    for (int i = 0; i < list.size() ;i++)
    {
        if(i%3 == 0) row++;
        gridLayout->addWidget(list.at(i), row, (i+1) - ( 3 * (row - 3)));
        connect(list.at(i), &WidgetItem::emitSignal,this, &MainHelpContentsWidget::emitSignal);
    }
}
/*!
 * \brief update pictures in layout
 */
void MainHelpContentsWidget::updatePixmaps()
{
    for (int i = 0; i < m_list.size(); i++)
    {
        m_list[i]->updatePixmap();
    }
}
/*!
 * \brief set width of widgets
 * \param width
 */
void MainHelpContentsWidget::setWidth(double width)
{
    int spacing = 20;
    setFixedWidth(width - spacing);
    QRect geo = m_layout->geometry();
    m_layout->setGeometry(QRect(geo.x(), geo.y(), width - spacing, geo.height()));
    label->setFixedWidth(width - spacing);
    labelText->setFixedWidth(width - spacing);
    updatePixmaps();
}
/*!
 * \brief set height of widget
 * \param height
 */
void MainHelpContentsWidget::setHeight(double height)
{
    setFixedHeight(height);
    updatePixmaps();
}
