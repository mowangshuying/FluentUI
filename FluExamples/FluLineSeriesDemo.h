#pragma once

#include "FluTemplateDemo.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include "../FluUtils/FluUtils.h"
#include <QValueAxis>

class FluLineSeriesDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluLineSeriesDemo(QWidget *parent = nullptr)
    {
        setWindowTitle(tr("LineSeries Demo"));
        QList<QLineSeries *> m_series;

        QLineSeries *s1 = new QLineSeries;
        QLineSeries *s2 = new QLineSeries;

        m_series.append(s1);
        m_series.append(s2);

        // set name;
        s1->setName("s1");
        s2->setName("s2");

        // set line colr;
        s1->setColor(QColor(255, 0, 255));
        s2->setColor(QColor(0, 255, 255));
        // series1->setBrush(QColor(255,0,255));
        // series1->setPen(QColor(255,0,255));

        // set line visible
        s1->setVisible(true);
        s2->setVisible(true);

        // set point labels visible
        s1->setPointLabelsVisible(true);
        s2->setPointLabelsVisible(true);

        // set point labels color
        // s1->setPointLabelsColor(QColor(255,255,255));
        // s2->setPointLabelsColor(QColor(255,255,255));
        s1->setPointLabelsColor(Qt::black);
        s2->setPointLabelsColor(Qt::black);

        // set point labels font
        s1->setPointLabelsFont(QFont("微软雅黑"));
        s2->setPointLabelsFont(QFont("微软雅黑"));

        // point labels setttings
        // set point labels format
        s1->setPointLabelsFormat("(@xPoint,@yPoint)");
        s2->setPointLabelsFormat("(@xPoint,@yPoint)");

        // set point labels clipping
        s1->setPointLabelsClipping(false);
        s2->setPointLabelsClipping(true);

        s1->setPointLabelsVisible(false);
        s2->setPointLabelsVisible(false);

        // set points visible
        s1->setPointsVisible(true);
        s2->setPointsVisible(true);

        // append points
        s1->append(0, 6);
        s1->append(1, 4);
        s1->append(2, 8);
        s1->append(3, 4);
        s1->append(4, 5);
        s1->append(5, 6);
        s1->append(6, 4);
        s1->append(7, 8);
        s1->append(8, 4);
        s1->append(9, 5);

        // *s1 << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

        s2->append(0, 8);
        s2->append(2, 5);
        s2->append(3, 3);
        s2->append(7, 9);
        s2->append(10, 2);

        // *s2 << QPointF(11, 3) << QPointF(13, 8) << QPointF(17, 2) << QPointF(18, 5) << QPointF(20, 7);

        QChart *chart = new QChart();
        // chart->setTheme(QChart::ChartThemeLight);
        // chart->setAnimationOptions(QChart::AllAnimations);

        // set background color; choose one of the theme or background color
        chart->setBackgroundBrush(QBrush(QColor(243, 243, 243)));

        // set shadow enabled
        // chart->setDropShadowEnabled(true);

        // set locale numbers
        chart->setLocalizeNumbers(true);

        // show legend
        // chart->legend()->show();

        // add s1;
        chart->addSeries(s1);

        // add s2;
        chart->addSeries(s2);

        // x; y;
        auto xAxis = new QValueAxis;
        auto yAxis = new QValueAxis;

        xAxis->setRange(0, 30);
        yAxis->setRange(0, 30);

        xAxis->setTitleText("X");
        yAxis->setTitleText("Y");

        xAxis->setLabelFormat("%.1f");
        xAxis->setTickCount(11);
        xAxis->setMinorTickCount(2);
        yAxis->setLabelFormat("%.1f");
        yAxis->setTickCount(11);
        yAxis->setMinorTickCount(2);

        chart->addAxis(xAxis, Qt::AlignBottom);
        chart->addAxis(yAxis, Qt::AlignLeft);

        s1->attachAxis(xAxis);
        s1->attachAxis(yAxis);
        s2->attachAxis(xAxis);
        s2->attachAxis(yAxis);

        chart->setTitle("Simple line chart example");
        chart->setTitleBrush(QBrush(Qt::black));
        chart->setTitleFont(QFont("微软雅黑", 18));

        // chart->legend()->setVisible(true);
        // chart->legend()->setAlignment(Qt::AlignBottom);
        // chart->legend()->detachFromChart();
        // chart->legend()->setBackgroundVisible(true);
        // chart->legend()->setAutoFillBackground(true);
        // chart->legend()->setColor(QColor(255,128,128,128));
        // chart->legend()->setContentsMargins(10,10,10,10);
        // chart->legend()->setLabelColor(QColor(255,128,255));
        // chart->legend()->setVisible(true);
        // chart->legend()->setMaximumHeight(50);
        // chart->legend()->setMaximumWidth(120);
        // chart->legend()->setMaximumSize(10000);
        // chart->legend()->setGeometry(50,50,120,50);
        // chart->legend()->setBrush(QBrush(QColor(128,128,128,128)));
        // chart->legend()->setPen(QPen(QColor(192,192, 192,192)));
        // chart->legend()->setBorderColor(QColor(255,255,170,185));
        // QFont font = chart->legend()->font();
        // font.setItalic(!font.italic());
        // chart->legend()->setFont(font);
        // font.setPointSizeF(12);
        // chart->legend()->setFont(font);
        // chart->legend()->setFont(QFont("微软雅黑"));

        QChartView *chartView = new QChartView(chart);
        chartView->setContentsMargins(0, 0, 0, 0);
        chartView->setRenderHint(QPainter::Antialiasing);

        m_contentLayout->addWidget(chartView);

        onThemeChanged();
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, &FluLineSeriesDemo::onThemeChanged);
    }

  public slots:
    void onThemeChanged()
    {
        FluStyleSheetUitls::setQssByFileName("FluLineSeriesDemo.qss", this, FluThemeUtils::getUtils()->getTheme());
    }
};