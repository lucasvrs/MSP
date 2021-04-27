#include "subjecthelpcontentswidget.h"
#include "widgetitem.h"

#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDebug>
#include <QPushButton>
/*!
 * \brief Constructor
 * \param item widgetitem which is shown
 * \param parent
 */
SubjectHelpContentsWidget::SubjectHelpContentsWidget(WidgetItem *item, QWidget *parent) :
    QWidget(parent)
{

    QPushButton *button = new QPushButton;
    m_layout = new QVBoxLayout(this);
    m_labelName = new QLabel;
    m_description = new QLabel;

    QLabel* desHead = new QLabel;
    desHead->setText("Description");
    desHead->setAlignment(Qt::AlignCenter);
    desHead->setFixedHeight(20);

    QLabel* funcHead = new QLabel;
    funcHead->setText("Functionality");
    funcHead->setAlignment(Qt::AlignCenter);
    funcHead->setFixedHeight(20);

    QLabel* funcLabel = new QLabel;
    funcLabel->setText(item->func());
    funcLabel->setAlignment(Qt::AlignCenter);
    funcLabel->setFixedHeight(200);

    QLabel* shortHead = new QLabel;
    shortHead->setText("Shortcuts");
    shortHead->setAlignment(Qt::AlignCenter);
    shortHead->setFixedHeight(20);




    m_labelName->setFixedHeight(100);
    m_labelName->setText(item->name());
    m_description->setFixedHeight(300);

    button->setText("Back to Menu");

    m_description->setText(item->description());
    m_pictureLabel = new QLabel();
    m_pictureLabel->setAlignment(Qt::AlignCenter);
    m_labelName->setAlignment(Qt::AlignCenter);
    m_description->setAlignment(Qt::AlignCenter);


    QGridLayout *grLayout = new QGridLayout;


    int row = 1;
    bool first = true;
    for (int i = 0; i < item->shortList().size() ;i++)
    {
        if(first)
        {
            QLabel *labelA = new QLabel;
            labelA->setText("Key Combination");
            labelA->setAlignment(Qt::AlignCenter);
            labelA->setFixedHeight(20);


            QLabel *labelB = new QLabel;
            labelB->setText("Function");
            labelB->setAlignment(Qt::AlignCenter);
            labelB->setFixedHeight(20);

            grLayout->addWidget(labelA, row, 1);
            grLayout->addWidget(labelB, row, 2);
            i--;
            first = false;

        }
        else
        {

        if(i%2 == 0) row++;

        Shortcut shorty = item->shortList().at(i);
        QLabel *labelA = new QLabel;
        labelA->setText(shorty.shorty);
        labelA->setAlignment(Qt::AlignCenter);
        labelA->setFixedHeight(20);


        QLabel *labelB = new QLabel;
        labelB->setText(shorty.shortyFunc);
        labelB->setAlignment(Qt::AlignCenter);
        labelB->setFixedHeight(20);

        grLayout->addWidget(labelA, row, 1);
        grLayout->addWidget(labelB, row, 2);
}

    }



    QPixmap pic(item->picLink());

    m_pictureLabel->setPixmap(pic);
    m_layout->addWidget(button);
    m_layout->addWidget(m_labelName);
    m_layout->addWidget(m_pictureLabel);
    m_layout->addWidget(desHead);
    m_layout->addWidget(m_description);
    m_layout->addWidget(funcHead);
    m_layout->addWidget(funcLabel);
    m_layout->addWidget(shortHead);
    m_layout->addLayout(grLayout);



    connect(button, &QPushButton::clicked, [this]()
    {
        emit emitSignal();
    });
}

void SubjectHelpContentsWidget::btn_clicked()
{
    emit emitSignal();
}
/*!
 * \brief set width of widget
 * \param width
 */
void SubjectHelpContentsWidget::setWidth(double width)
{
    int spacing = 20;
    setFixedWidth(width - spacing);
    QRect geo = m_layout->geometry();
    m_layout->setGeometry(QRect(geo.x(), geo.y(), width - spacing, geo.height()));
}
