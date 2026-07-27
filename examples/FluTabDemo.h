#pragma once

#include <QTabWidget>
#include "../Controls/FluWidget.h"

#include "../Controls/FluTabWidget.h"
#include "FluButtonDemo.h"
#include "FluChangeBgDemo.h"
#include "FluColorDemo.h"
#include "../Controls/FluLabel.h"

class FluTabPage : public FluWidget
{
    Q_OBJECT
  public:
    FluTabPage(QString text, QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();
};

class FluTabDemo : public FluTabWidget
{
    Q_OBJECT
  public:
    FluTabDemo(QWidget* parent = nullptr);

  private:
};
