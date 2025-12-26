#pragma once

#include "FluTemplateDemo.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include "../FluUtils/FluUtils.h"
#include <QValueAxis>

// #include <QtCharts>

#if QT_VERSION <= QT_VERSION_CHECK(6, 0, 0)
using namespace QtCharts;
#endif

class FluLineSeriesDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluLineSeriesDemo(QWidget *parent = nullptr);

  public slots:
    void onThemeChanged();
};