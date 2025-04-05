#pragma once

#include <QTabWidget>
#include "../FluControls/FluWidget.h"

#include "../FluControls/FluTabWidget.h"
#include "FluButtonDemo.h"
#include "FluChangeBgDemo.h"
#include "FluColorDemo.h"
#include "../FluControls/FluLabel.h"

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
    FluTabDemo(QWidget *parent = nullptr);
  private:
};
