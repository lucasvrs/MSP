#include "widgetitem.h"
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QLabel>
#include <qgraphicsscene.h>
#include <QDebug>
#include <QStyleOption>
#include <QPainter>
#include "helpwidget.h"

/*!
 * \brief Constructor
 * \param parent
 */
WidgetItem::WidgetItem(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    setCursor(Qt::PointingHandCursor);
    setFixedHeight(200);

    QVBoxLayout* layout = new QVBoxLayout(this);
    m_line = new QLabel("Text");
    m_line->setAlignment(Qt::AlignCenter);
    m_line->setFixedHeight(30);
    m_pic = new QLabel("Picture");
    m_pic->setAlignment(Qt::AlignCenter);

    layout->addWidget(m_line);
    layout->addWidget(m_pic);
}

void WidgetItem::mouseReleaseEvent(QMouseEvent *event)
{
   emit emitSignal(this);
    QWidget::mouseReleaseEvent(event);

}



QString WidgetItem::picLink() const
{
    return m_picLink;
}

void WidgetItem::setPicLink(const QString &picLink)
{
    m_picLink = picLink;
    m_map = QPixmap(picLink);
    if(m_map.isNull()) return;
    m_pic->setPixmap(m_map.scaled(width(), height(), Qt::KeepAspectRatio));
}

QString WidgetItem::description() const
{
    return m_description;
}

void WidgetItem::setDescription(const QString &description)
{
    m_description = description;
}

QString WidgetItem::name() const
{
    return m_name;
}

void WidgetItem::setName(const QString &name)
{
    m_name = name;
    m_line->setText(name);
}

QList<Shortcut> WidgetItem::shortList() const
{
    return m_shortList;
}

void WidgetItem::setShortList(const QList<Shortcut> &shortList)
{
    m_shortList = shortList;
}

QString WidgetItem::func() const
{
    return m_func;
}

void WidgetItem::setFunc(const QString &func)
{
    m_func = func;
}

QPixmap WidgetItem::map() const
{
    return m_map;
}

void WidgetItem::setMap(const QPixmap &map)
{
    m_map = map;
}

//SLOTS*************************************************
void WidgetItem::updatePixmap()
{
    if(m_map.isNull()) return;
    m_pic->setPixmap(m_map.scaled(width(), height(), Qt::KeepAspectRatio));
}

//EVENTS*************************************************
void WidgetItem::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
