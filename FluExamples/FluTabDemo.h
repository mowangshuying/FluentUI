#pragma once

#include <QTabWidget>
#include <QWidget>

#include "../FluControls/FluTabWidget.h"
#include "FluButtonDemo.h"
#include "FluChangeBgDemo.h"
#include "FluColorDemo.h"

class FluTabDemo : public FluTabWidget {
  Q_OBJECT
public:
  FluTabDemo(QWidget *parent = nullptr);

  void addColorExampleWidget();

  void addChangeBackgrondWidget();

  void addButtonExmapleWidget();

private:
};
