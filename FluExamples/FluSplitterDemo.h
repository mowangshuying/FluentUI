#pragma once

#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QFrame>
#include "FluTemplateDemo.h"
#include "../FluUtils/FluUtils.h"

class FluSplitterDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluSplitterDemo(QWidget* parent = nullptr);
};
