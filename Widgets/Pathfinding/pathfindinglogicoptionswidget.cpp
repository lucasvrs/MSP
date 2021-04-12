#include "pathfindinglogicoptionswidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDebug>
#include <QPushButton>

PathfindingLogicOptionsWidget::PathfindingLogicOptionsWidget(QWidget *parent) : QWidget(parent), m_changes(false)
{
    QGridLayout* layout = new QGridLayout(this);
    QLabel* startNodeLabel = new QLabel("Start-Node:");
    QLabel* startRowLabel = new QLabel("Row:");
    QLabel* startColLabel = new QLabel("Column:");
    QLabel* destNodeLabel = new QLabel("Destination-Node:");
    QLabel* destRowLabel = new QLabel("Row:");
    QLabel* destColLabel = new QLabel("Column:");
    m_startRowSpinBox = new QSpinBox;
    m_startRowSpinBox->setRange(1, 25);
    m_startColSpinBox = new QSpinBox;
    m_startColSpinBox->setRange(1, 25);
    m_destRowSpinBox = new QSpinBox;
    m_destRowSpinBox->setRange(1, 25);
    m_destColSpinBox = new QSpinBox;
    m_destColSpinBox->setRange(1, 25);
    QSpacerItem* hSpacer = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* vSpacer = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QPushButton* cancelBtn = new QPushButton("Cancel");
    QPushButton* applyBtn = new QPushButton("Apply");
    QPushButton* saveBtn = new QPushButton("Save");
    layout->addWidget(startNodeLabel, 0, 0);
    layout->addWidget(startRowLabel, 1, 0);
    layout->addWidget(m_startRowSpinBox, 1, 1);
    layout->addWidget(startColLabel, 2, 0);
    layout->addWidget(m_startColSpinBox, 2, 1);

    layout->addWidget(destNodeLabel, 0, 2);
    layout->addWidget(destRowLabel, 1, 2);
    layout->addWidget(m_destRowSpinBox, 1, 3);
    layout->addWidget(destColLabel, 2, 2);
    layout->addWidget(m_destColSpinBox, 2, 3);

    layout->addItem(hSpacer, 1, 4);
    layout->addItem(vSpacer, 3, 0);

    layout->addWidget(cancelBtn, 4, 5);
    layout->addWidget(applyBtn, 4, 6);
    layout->addWidget(saveBtn, 4, 7);

    connect(cancelBtn, &QPushButton::clicked, [this]()
    {
        m_changes = false;
        closeOptions();
    });
    connect(saveBtn, &QPushButton::clicked, [this]()
    {
        if(m_changes)
        {
            applyChanges();
            m_changes = false;
        }
        closeOptions();
    });
    connect(applyBtn, &QPushButton::clicked, [this]()
    {
        m_changes = true;
    });
}

//SLOTS***************************************************************************
void PathfindingLogicOptionsWidget::setDestRow(int i)
{
    m_destRowSpinBox->setValue(i);
}

void PathfindingLogicOptionsWidget::setStartRow(int i)
{
    m_startRowSpinBox->setValue(i);
}

void PathfindingLogicOptionsWidget::setDestCol(int i)
{
    m_destColSpinBox->setValue(i);
}

void PathfindingLogicOptionsWidget::setStartCol(int i)
{
    m_startColSpinBox->setValue(i);
}

void PathfindingLogicOptionsWidget::applyChanges()
{
    int dCol = m_destColSpinBox->value();
    int dRow = m_destRowSpinBox->value();
    int sCol = m_startColSpinBox->value();
    int sRow = m_startRowSpinBox->value();
    if(dRow == sRow && dCol == sCol)
    {
        return;
    }
    emit delimiterPosChanged(sCol - 1, sRow - 1, dCol - 1, dRow - 1);
}
