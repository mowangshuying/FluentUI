#pragma once

#include "FluTemplateDemo.h"
#include <QTableWidget>
#include <QHeaderView>
#include "../Controls/FluScrollDelegate.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../Controls/FluPushButton.h"

class FluTableViewDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluTableViewDemo(QWidget* parent = nullptr);
};
