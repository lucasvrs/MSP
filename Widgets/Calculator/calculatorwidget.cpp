/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Andreas Heidenreich
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "calculatorwidget.h"
#include "calculator.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QRegExpValidator>
#include <QDebug>

CalculatorWidget::CalculatorWidget(QWidget *parent) : QWidget(parent)
{
    m_calc = new Calculator;

    //layout
    QGridLayout* layout = new QGridLayout(this);
    QSpacerItem* hSpacerL = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* hSpacerR = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* vSpacerT = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem* vSpacerB = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->setSpacing(1);
    m_edit = new QLineEdit;
    layout->addItem(vSpacerT, 0, 1);
    layout->addItem(hSpacerL, 1, 0);
    layout->addWidget(m_edit, 2, 1, 1, 5);
    int row = 2;
    for(int i = 0; i < 9; i++)
    {
        if(i%3 == 0) row++;
        QPushButton* btn = new QPushButton(QString::number(i + 1));
        btn->setObjectName("numberBtn");
        layout->addWidget(btn, row, (i + 1) - (3 * (row - 3)));
        connect(btn, &QPushButton::clicked, [this, btn]()
        {
            addNumber(btn->text());
        });
    }
    QPushButton* clearBtn = new QPushButton("AC");
    clearBtn->setObjectName("highlightBtn");
    QPushButton* zeroBtn = new QPushButton("0");
    zeroBtn->setObjectName("numberBtn");
    QPushButton* commaBtn = new QPushButton(".");
    connect(commaBtn, &QPushButton::clicked, [this, commaBtn]()
    {
        m_edit->setText(m_edit->text() + commaBtn->text());
    });
    layout->addWidget(clearBtn, 6, 1);
    layout->addWidget(zeroBtn, 6, 2);
    layout->addWidget(commaBtn, 6, 3);
    QPushButton* addBtn = new QPushButton("+");
    QPushButton* subBtn = new QPushButton("-");
    QPushButton* multBtn = new QPushButton("*");
    QPushButton* divBtn = new QPushButton("/");
    QPushButton* powBtn = new QPushButton("^");
    QPushButton* moduloBtn = new QPushButton("mod");
    m_actions = {addBtn, subBtn, multBtn, divBtn, powBtn, moduloBtn};
    QPushButton* equalsBtn = new QPushButton("=");
    connect(equalsBtn, &QPushButton::clicked, this, &CalculatorWidget::calcResult);
    layout->addWidget(powBtn, 3, 4);
    layout->addWidget(moduloBtn, 3, 5);
    layout->addWidget(addBtn, 4, 4);
    layout->addWidget(subBtn, 4, 5);
    layout->addWidget(multBtn, 5, 4);
    layout->addWidget(divBtn, 5, 5);
    layout->addWidget(equalsBtn, 6, 4, 1, 2);
    layout->addItem(vSpacerB, 7, 1);
    layout->addItem(hSpacerR, 1, 6);

    for(QPushButton* btn : m_actions)
    {
        connect(btn, &QPushButton::clicked, [this, btn]()
        {
            addOperator(btn->text());
        });
    }
    connect(clearBtn, &QPushButton::clicked, [this]()
    {
        m_edit->setText("");
    });
    connect(zeroBtn, &QPushButton::clicked, [this, zeroBtn]()
    {
        addNumber(zeroBtn->text());
    });
}

double CalculatorWidget::calc(const QString& o, double a, double b)
{
    Calculator::Operator op = m_calc->ops[m_calc->opStr.indexOf(o)];
    return m_calc->action(op, a, b);
}

//SLOTS*********************************************************
/*! Adds number to line edit
 * \brief CalculatorWidget::addNumber
 * \param n - number
 */
void CalculatorWidget::addNumber(const QString& n)
{
    int lastIndex = -1;
    QString text = m_edit->text();
    for(int i = 0; i < Calculator::Operators; i++)
    {
        int index = text.lastIndexOf(m_calc->opStr[i]);
        if(index > lastIndex)
        {
            lastIndex = index;
        }
    }
    if(lastIndex == text.size() - 2 && text[text.size() - 1] == "0")
    {
        m_edit->setText(text.left(text.size() - 1) + n);
    }
    else
    {
        m_edit->setText(text + n);
    }
}

/*! Adds operator to line edit
 * \brief CalculatorWidget::addOperator
 * \param o - operator
 */
void CalculatorWidget::addOperator(const QString& o)
{
    QString text = m_edit->text();
    if(text.isEmpty()) return;
    for(int i = 0; i < Calculator::Operators; i++)
    {
        if(text[text.size() - 1] == m_calc->opStr[i])
        {
            m_edit->setText(text.left(text.size() - 1) + o);
            return;
        }
    }
    m_edit->setText(text + o);
}

/*! Calculates result of the term in line edit
 * \brief CalculatorWidget::calcResult
 */
void CalculatorWidget::calcResult()
{
    QString text = m_edit->text();
    if(text.isEmpty()) return;
    for(int i = 0; i < Calculator::Operators; i++)
    {
        if(text[text.size() - 1] == m_calc->opStr[i])
        {
            return;
        }
    }
    QRegExp numberSep("[(*|/|-|+|^|mod)]");
    QRegExp operatorSep("[0-9.]");
    QStringList operators = text.split(operatorSep, QString::SkipEmptyParts);
    QStringList numbers = text.split(numberSep, QString::SkipEmptyParts);
    bool found = false;
    int startPrio = 3;
    if(operators.isEmpty()) return;
    while(numbers.size() > 1)
    {
        for(int i = 0; i < operators.length(); i++)
        {
            if(m_calc->prio[m_calc->opStr.indexOf(operators[i])] == startPrio)
            {
                numbers[i] = QString::number(calc(operators[i], numbers[i].toDouble(), numbers[i + 1].toDouble()));
                numbers.removeAt(i + 1);
                operators.removeAt(i);
                found = true;
                break;
            }
        }
        if(!found)
        {
            startPrio--;
        }
        found = false;
    }
    m_edit->setText(numbers[0]);
}
