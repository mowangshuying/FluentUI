#pragma once

#include "FluTemplateDemo.h"
#include <QTableWidget>
#include <QHeaderView>
#include "../controls/FluScrollDelegate.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../controls/FluPushButton.h"

class FluTableViewDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluTableViewDemo(QWidget* parent = nullptr);
};
