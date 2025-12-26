#pragma once

#include "FluTemplateDemo.h"
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QChart>

#if QT_VERSION <= QT_VERSION_CHECK(6, 0, 0)
using namespace QtCharts;
#endif

class FluPieSeriesDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluPieSeriesDemo(QWidget *parent = nullptr) : FluTemplateDemo(parent)
    {
        setWindowTitle(tr("PieSeries Demo"));

        QPieSeries *series = new QPieSeries();
        // series->setHoleSize(0.30);

        // set every sector color;
        QStringList colors = {"#1060DC", "#00B553", "#EF7302", "#C71969", "#8AC114"};

        // set data;
        QList<qreal> values = {10, 20, 30, 25, 15};
        for (int i = 0; i < 5; i++)
        {
            QPieSlice *slice = series->append(QString("Sector %1").arg(i), values[i]);
            slice->setLabelVisible();
            slice->setBrush(QColor(colors[i]));
            series->append(slice);
        }

        // chart;
        QChart *chart = new QChart();
        chart->setTitle("Pie Series Example");
        chart->addSeries(series);

        // chart view;
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setChart(chart);

        m_contentLayout->addWidget(chartView);
    }

  public slots:
    void onThemeChanged()
    {
    }
};
