#pragma once

#include "FluTemplateDemo.h"
#include <QTableWidget>
#include <QHeaderView>
#include "../FluControls/FluScrollDelegate.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../FluControls/FluPushButton.h"

class FluTableViewDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluTableViewDemo(QWidget* parent = nullptr);
};
