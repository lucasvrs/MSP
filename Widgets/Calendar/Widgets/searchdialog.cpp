#include "searchdialog.h"
#include "Utils/constants.h"
#include <QGridLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QDateTime>
#include <QPushButton>
#include <QDebug>

SearchDialog::SearchDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f)
{
    setWindowTitle("Search");

    //defines layout
    QGridLayout* layout = new QGridLayout(this);
    m_date = new QDate(QDateTime::currentDateTime().date());
    m_month = new QComboBox;
    m_month->addItems(MONTHS);
    m_day = new QSpinBox;
    m_day->setMinimum(1);
    m_year = new QSpinBox;
    m_year->setMinimum(1900);
    m_year->setMaximum(2200);
    QPushButton* cancelBtn = new QPushButton("Cancel");
    QPushButton* applyBtn = new QPushButton("Apply");
    layout->addWidget(m_day, 0, 0);
    layout->addWidget(m_month, 0, 1);
    layout->addWidget(m_year, 0, 2);
    layout->addWidget(cancelBtn, 1, 1);
    layout->addWidget(applyBtn, 1, 2);

    fitToDate();

    //connects
    connect(m_day, QOverload<int>::of(&QSpinBox::valueChanged), [this](int i)
    {
        m_date->setDate(m_date->year(), m_date->month(), i);
        fitToDate();
    });
    connect(m_month, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int i)
    {
        m_date->setDate(m_date->year(), i + 1, m_date->day());
        fitToDate();
    });
    connect(m_year, QOverload<int>::of(&QSpinBox::valueChanged), [this](int i)
    {
        m_date->setDate(i, m_date->month(), m_date->day());
        fitToDate();
    });
    connect(cancelBtn, &QPushButton::clicked, [this]()
    {
        close();
    });
    connect(applyBtn, &QPushButton::clicked, [this]()
    {
        emit dateChanged(*m_date);
        close();
    });
}

//EVENTS******************************************************************************************
void SearchDialog::closeEvent(QCloseEvent* e)
{
    emit closed();
    QDialog::closeEvent(e);
}

//SLOTS*******************************************************************************************
/*! Sets values of dialog to a certain date
 * \brief SearchDialog::fitToDate
 */
void SearchDialog::fitToDate()
{
    m_day->setMaximum(m_date->daysInMonth());
    m_day->setValue(m_date->day());
    m_month->setCurrentIndex(m_date->month() - 1);
    m_year->setValue(m_date->year());
}
