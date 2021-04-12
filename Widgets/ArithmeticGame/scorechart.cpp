#include "scorechart.h"
#include <QLayout>
#include <QDebug>
#include <QDir>


/*!
 * \brief Konstruktor
 * \param parent QWidget
 */
ScoreChart::ScoreChart(QWidget *parent) : QDialog(parent)
{
      getSeries();
      costumizeChart();
      costumizeAxis();
      m_chartView = new QtCharts::QChartView(m_chart);
      m_chartView->setRenderHint(QPainter::Antialiasing);

}

/*!
 * \brief Deskonstruktor
 */
ScoreChart::~ScoreChart()
{
    delete ui;
}

QtCharts::QChartView *ScoreChart::getChartView() const
{
    return m_chartView;
}
/*!
 * \brief gets the last scores with help of a TXT-Reader
 */
void ScoreChart::getSeries()
{


     m_scoreSeries = new QtCharts::QLineSeries();

     m_scoreReader = new TXTReader();
     QString path = QDir().absolutePath() + "/../Kopfrechnen" + "/KopfrechnenScore";
     m_ScoreVector = m_scoreReader->getInput(path.toUtf8().constData());

     switch(m_ScoreVector.length()){
       case(0):
         break;
       case(1):
         *m_scoreSeries << QPointF(1, std::stoi(m_ScoreVector.at(0)));
         break;
       case(2):
         *m_scoreSeries << QPointF(1, std::stoi(m_ScoreVector.at(0))) << QPointF(2, std::stoi(m_ScoreVector.at(1)));
         break;
       case(3):
         *m_scoreSeries << QPointF(1, std::stoi(m_ScoreVector.at(0))) << QPointF(2, std::stoi(m_ScoreVector.at(1))) << QPointF(3, std::stoi(m_ScoreVector.at(2)));
         break;
       case(4):
         *m_scoreSeries << QPointF(1, std::stoi(m_ScoreVector.at(0))) << QPointF(2, std::stoi(m_ScoreVector.at(1))) << QPointF(3, std::stoi(m_ScoreVector.at(2))) << QPointF(4, std::stoi(m_ScoreVector.at(3)));
         break;
       case(5):
         *m_scoreSeries << QPointF(1, std::stoi(m_ScoreVector.at(0))) << QPointF(2, std::stoi(m_ScoreVector.at(1))) << QPointF(3, std::stoi(m_ScoreVector.at(2))) << QPointF(4, std::stoi(m_ScoreVector.at(3))) << QPointF(5, std::stoi(m_ScoreVector.at(4)));
         break;


     }
     getMaximum(m_ScoreVector);


     m_chart = new QtCharts::QChart();
     m_chart->legend()->hide();
     m_chart->addSeries(m_scoreSeries);


}
/*!
 * \brief sets Color and background of chart
 */
void ScoreChart::costumizeChart()
{
    // Customize series
        QPen pen(QRgb(0xfdb157));
        pen.setWidth(5);
        m_scoreSeries->setPen(pen);

        // Customize chart title
        QFont font;
        font.setPixelSize(18);
        m_chart->setTitleFont(font);
        m_chart->setTitleBrush(QBrush(Qt::white));
        m_chart->setTitle("Last five games");

        // Customize chart background
        QLinearGradient backgroundGradient;
        backgroundGradient.setStart(QPointF(0, 0));
        backgroundGradient.setFinalStop(QPointF(0, 1));
        backgroundGradient.setColorAt(0.0, QRgb(0xF508E5));
        backgroundGradient.setColorAt(1.0, QRgb(0x9E1194));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chart->setBackgroundBrush(backgroundGradient);

        // Customize plot area background
        QLinearGradient plotAreaGradient;
        plotAreaGradient.setStart(QPointF(0, 1));
        plotAreaGradient.setFinalStop(QPointF(1, 0));
        plotAreaGradient.setColorAt(0.0, QRgb(0x33FFF));
        plotAreaGradient.setColorAt(1.0, QRgb(0x00FFF));
        plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chart->setPlotAreaBackgroundBrush(plotAreaGradient);
        m_chart->setPlotAreaBackgroundVisible(true);

}
/*!
 * \brief costumize the Axis
 */
void ScoreChart::costumizeAxis()
{
       QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis();
       QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();

       // Customize axis label font
       QFont labelsFont;
       labelsFont.setPixelSize(12);
       axisX->setLabelsFont(labelsFont);
       axisY->setLabelsFont(labelsFont);

       // Customize axis colors
       QPen axisPen(QRgb(0xd18952));
       axisPen.setWidth(2);
       axisX->setLinePen(axisPen);
       axisY->setLinePen(axisPen);

       // Customize axis label colors
       QBrush axisBrush(Qt::white);
       axisX->setLabelsBrush(axisBrush);
       axisY->setLabelsBrush(axisBrush);

       // Customize grid lines and shades
       axisX->setGridLineVisible(false);
       axisY->setGridLineVisible(false);
       axisY->setShadesPen(Qt::NoPen);
       axisY->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
       axisY->setShadesVisible(true);

       axisX->setRange(1,5);
       axisY->setRange(0,m_maximum + 20);
       m_chart->addAxis(axisX, Qt::AlignBottom);
       m_chart->addAxis(axisY, Qt::AlignLeft);
       m_scoreSeries->attachAxis(axisX);
       m_scoreSeries->attachAxis(axisY);

}
/*!
 * \brief calculates the highest score of the last games
 * \param scores QVector<std::string> the last scores
 */
void ScoreChart::getMaximum(QVector<std::string> scores)
{
   auto hlp = std::stoi(scores.at(1));
   for (auto i = 1; i< scores.length()-1 ; i++ ) {
       if(hlp < std::stoi(scores.at(i))) hlp = std::stoi(scores.at(i));
   }

   m_maximum = hlp;


}
