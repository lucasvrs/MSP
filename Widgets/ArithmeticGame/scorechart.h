#ifndef SCORECHART_H
#define SCORECHART_H

#include <QDialog>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include "Txt/txtreader.h"
#include "Txt/txtwriter.h"
#include <QVector>


namespace Ui {
class ScoreChart;
}

class ScoreChart : public QDialog
{


public:
    explicit ScoreChart(QWidget* parent = nullptr);
    ~ScoreChart();

    QtCharts::QChartView *getChartView() const;

private:
    Ui::ScoreChart *ui;
    QtCharts::QLineSeries *m_scoreSeries;
    QtCharts::QChart *m_chart;
    TXTReader *m_scoreReader;
    TXTWriter *m_scoreWriter;
    QVector<std::string> m_ScoreVector;
    QtCharts::QChartView *m_chartView;
    int m_maximum;

    void getSeries();
    void costumizeChart();
    void costumizeAxis();
    void getMaximum(QVector<std::string> scores);

};

#endif // SCORECHART_H
