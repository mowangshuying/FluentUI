#pragma once

#include "FluTemplateDemo.h"
#include "../Controls/FluTableView.h"

class FluTableViewExDemo : public FluTemplateDemo
{
  public:
    FluTableViewExDemo(QWidget* parent = nullptr);

  public:
    // QHBoxLayout* m_hLayout;
    FluTableView* m_tableView;
};
