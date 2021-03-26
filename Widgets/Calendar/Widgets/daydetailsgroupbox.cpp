#include "daydetailsgroupbox.h"
#include "Xml/xmlreader.h"
#include "Xml/xmlwriter.h"
#include <QDate>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <QPushButton>
#include <QCheckBox>
#include <QListWidget>
#include <QDomElement>

DayDetailsGroupBox::DayDetailsGroupBox(const QDate& date, QWidget *parent) :
    QGroupBox(parent)
{
    //current date
    m_date = new QDate(date.year(), date.month(), date.day());

    //background style
    setAutoFillBackground(true);
    QPalette p;
    p.setColor(QPalette::Window, Qt::white);
    setPalette(p);

    //defines and initializes list widget
    m_listW = new QListWidget;
    m_listW->addItems(allAppointments());
    QListWidgetItem* item = nullptr;
    for(int i = 0; i < m_listW->count(); i++)
    {
        item = m_listW->item(i);
        item->setFlags(item->flags() | Qt::ItemIsSelectable | Qt::ItemIsEditable);
    }

    //defines layout
    QGridLayout* layout = new QGridLayout(this);
    QLabel* headerLabel = new QLabel(date.toString("dd. MMMM yyyy"));
    headerLabel->setAlignment(Qt::AlignCenter);

    //defines options
    QPushButton* addBtn = new QPushButton("+");
    layout->addWidget(headerLabel, 0, 0, 1, 3);
    layout->addWidget(addBtn, 1, 0);
    layout->addWidget(m_listW, 2, 0, 1, 3);
    m_nameEdit = new QLineEdit;
    m_colorBtn = new QPushButton;
    m_saveBtn = new QPushButton("Save");
    m_cancelBtn = new QPushButton("Cancel");
    m_nameEdit->setPlaceholderText("Appointment title");
    layout->addWidget(m_colorBtn, 3, 0, 0);
    layout->addWidget(m_nameEdit, 3, 1, 1, 2);
    layout->addWidget(m_cancelBtn, 4, 1);
    layout->addWidget(m_saveBtn, 4, 2);

    hideAll();
    //connects
    connect(addBtn, &QPushButton::clicked, [this]()
    {
        showAll();
    });
    connect(m_cancelBtn, &QPushButton::clicked, [this]()
    {
        hideAll();
    });
    connect(m_saveBtn, &QPushButton::clicked, [this]()
    {
        hideAll();
        addEntry(m_nameEdit->text());
        m_nameEdit->setText("");
    });
}

/*! Reads and returns all appointments of a xml file
 * \brief DayDetailsGroupBox::allAppointments
 * \return
 */
QStringList DayDetailsGroupBox::allAppointments()
{
    QStringList strList;
    XMLReader reader("./../Kalender/appointments.xml");
    QDomElement year = reader.findElemUnderRoot("year", "id", QString::number(m_date->year()));
    QDomElement month = reader.findElemUnderElem(year, "month", "id", QString::number(m_date->month()));
    QDomElement day = reader.findElemUnderElem(month, "day", "id", QString::number(m_date->day()));
    for(QDomElement elem : *reader.allElemsUnderElem(day))
    {
        strList.append(elem.text());
    }
    return strList;
}

//SLOTS***************************************************************************************************
/*! Adds an certain structured entry to a xml file
 * \brief DayDetailsGroupBox::addEntry
 * \param entry
 */
void DayDetailsGroupBox::addEntry(const QString& entry)
{
    if(entry.isEmpty()) return;
    XMLWriter wr("./../Kalender/appointments.xml");
    QListWidgetItem* item = new QListWidgetItem(entry);
    item->setFlags(item->flags() | Qt::ItemIsSelectable | Qt::ItemIsEditable);
    m_listW->addItem(item);
    XMLReader reader("./../Kalender/appointments.xml");
    QDomElement year = reader.findElemUnderRoot("year", "id", QString::number(m_date->year()));
    if(year.isNull())
    {
        QDomNode node = wr.getElementByTagName("entries");
        QDomElement yearElem = wr.createElement("year");
        yearElem.setAttribute("id", QString::number(m_date->year()));
        QDomElement monthElem = wr.createElement("month");
        monthElem.setAttribute("id", QString::number(m_date->month()));
        QDomElement dayElem = wr.createElement("day");
        dayElem.setAttribute("id", QString::number(m_date->day()));
        wr.appendElementUnderElement(dayElem, "text", entry, "id", 1);
        wr.appendElementUnderElement(monthElem, dayElem);
        wr.appendElementUnderElement(yearElem, monthElem);
        wr.appendElementUnderElement(node, yearElem);
        wr.saveXML();
        emit needsUpdate(*m_date);
        return;
    }
    QDomElement month = reader.findElemUnderElem(year, "month", "id", QString::number(m_date->month()));
    if(month.isNull())
    {
        QDomNode node = wr.getElementByAttribute(year.tagName(), year.attribute("id"));
        QDomElement monthElem = wr.createElement("month");
        monthElem.setAttribute("id", QString::number(m_date->month()));
        QDomElement dayElem = wr.createElement("day");
        dayElem.setAttribute("id", QString::number(m_date->day()));
        wr.appendElementUnderElement(dayElem, "text", entry, "id", 1);
        wr.appendElementUnderElement(monthElem, dayElem);
        wr.appendElementUnderElement(node, monthElem);
        wr.saveXML();
        emit needsUpdate(*m_date);
        return;
    }
    QDomElement day = reader.findElemUnderElem(month, "day", "id", QString::number(m_date->day()));
    if(day.isNull())
    {
        QDomNode node = wr.getElementPerDate(year, month);
        QDomElement dayElem = wr.createElement("day");
        dayElem.setAttribute("id", QString::number(m_date->day()));
        wr.appendElementUnderElement(dayElem, "text", entry, "id", 1);
        wr.appendElementUnderElement(node, dayElem);
        wr.saveXML();
        emit needsUpdate(*m_date);
        return;
    }
    QDomNode node = wr.getElementPerDate(year, month, day);
    wr.appendElementUnderElement(node, "text", entry, "id", reader.allElemsUnderElem(day)->size() + 1);
    wr.saveXML();
    emit needsUpdate(*m_date);
}

/*! Hides all option buttons
 * \brief DayDetailsGroupBox::hideAll
 */
void DayDetailsGroupBox::hideAll()
{
    m_colorBtn->hide();
    m_saveBtn->hide();
    m_cancelBtn->hide();
    m_nameEdit->hide();
}

/*! Shows all option buttons
 * \brief DayDetailsGroupBox::showAll
 */
void DayDetailsGroupBox::showAll()
{
    m_colorBtn->show();
    m_saveBtn->show();
    m_cancelBtn->show();
    m_nameEdit->show();
}
