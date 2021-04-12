#include "epochenscene.h"
#include "constants.h"
#include "Xml/xmlreader.h"
#include "erabutton.h"
#include <QGraphicsLineItem>
#include <QDomDocument>
#include <QPushButton>
#include <QDir>
#include <QDebug>

EpochenScene::EpochenScene(QObject *parent) :
    QGraphicsScene(parent),
    m_initialized(false),
    m_widthMultiplier(1.0)
{
}

void EpochenScene::populateScene()
{
    double width = TIMELINE_BORDER * DIVISOR * m_widthMultiplier;
    double height = TIMELINE_HEIGHT / m_extraDivisor;
    m_extraDivisor = 2;
    if(!m_initialized)
    {
        getEras();
        m_initialized = true;
        m_extraDivisor = 1;
    }
    QGraphicsLineItem* timeline = new QGraphicsLineItem(-width - 25, height,
                                                        width + 25, height);
    timeline->setPos(0, 0);
    addItem(timeline);
    for(int i = -width; i <= width; i+=TEXT_SPACING * DIVISOR * m_widthMultiplier)
    {
        QGraphicsLineItem* line = new QGraphicsLineItem(i, height + 5, i, height - 5);
        addItem(line);
        QGraphicsTextItem* year = new QGraphicsTextItem(QString::number((i * MULTIPLICATOR) / m_widthMultiplier));
        year->setPos(i - year->boundingRect().width()/2, height + 20);
        addItem(year);
    }
    drawEras();
}

void EpochenScene::getEras()
{
    m_reader = new XMLReader("./../FinalMsp/Widgets/LiteratureEras/eras.xml");
    Language lan = ENGLISH;
    XMLNameConverter conv;
    conv.setCurLanguage(lan);
    QList<QDomElement> lang = *m_reader->allElemsUnderRoot();
    for(const QDomElement& el : lang)
    {
        if(el.tagName() == TOKEN[lan])
        {
            for(QDomElement era : *m_reader->allElemsUnderElem(el))
            {
                QList<int> years;
                conv.setCurName(era.tagName());
                for(QDomElement year : *m_reader->allElemsUnderElem(era))
                {
                    years.append(year.text().toInt());
                }
                m_eraNames.push_back(conv.convertedName());
                m_eraFroms.push_back(years[0]);
                m_eraTos.push_back(years[1]);
            }
            break;
        }
    }
}

void EpochenScene::drawEras()
{
    QFont font;
    font.setPointSize(FONT_SIZE);
    QFontMetrics fm(font);
    int layer = 1;
    int counter = 0;
    for(unsigned long i = 0; i < m_eraNames.size(); i++)
    {
        layer = 1;
        if(i != 0)
        {
            for(unsigned long j = 0; j < i; j++)
            {
                if(m_eraTos[j] >= m_eraFroms[i] && m_layers[j] == layer)
                {
                    layer++;
                    j = 0;
                }
            }
        }
        m_layers.push_back(layer);
        QString str = "";
        if(fm.width(m_eraNames[i]) < (m_eraTos[i] - m_eraFroms[i]) * DIVISOR * m_widthMultiplier)
        {
            str = m_eraNames[i];
        }
        EraButton* btn = new EraButton(str);
        btn->setGeometry(m_eraFroms[i] * DIVISOR * m_widthMultiplier, TIMELINE_HEIGHT / m_extraDivisor - 100 * m_layers[i],
                        (m_eraTos[i] - m_eraFroms[i]) * DIVISOR * m_widthMultiplier, 50);
        btn->setToolTip(m_eraNames[i]);
        btn->setColor(COLORS[counter]);
        btn->setFont(font);
        addItem(btn);
        counter++;
        if(counter == COLORS.length())
        {
            counter = 0;
        }
    }
}

void EpochenScene::unpopulateScene()
{
    for(QGraphicsItem* item : items())
    {
        removeItem(item);
    }
}

void EpochenScene::adjustWidthMultiplier(double value)
{
    m_widthMultiplier = value;
    unpopulateScene();
    populateScene();
}
