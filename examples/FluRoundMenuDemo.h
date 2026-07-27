#pragma once

#include <QWidget>
#include <QLabel>
#include "../Utils/FluUtils.h"
#include "../Controls/FluRoundMenu.h"
#include <QContextMenuEvent>
#include "FluTemplateDemo.h"
#include "../Controls/FluAction.h"
#include "../Controls/FluLabel.h"

class FluRoundMenuDemo : public FluTemplateDemo
{
  public:
    FluRoundMenuDemo(QWidget* parent = nullptr);

  protected:
    void contextMenuEvent(QContextMenuEvent* event);

  private:
    FluLabel* m_label;
};
