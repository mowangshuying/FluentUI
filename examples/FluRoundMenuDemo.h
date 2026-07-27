#pragma once

#include <QWidget>
#include <QLabel>
#include "../utils/FluUtils.h"
#include "../controls/FluRoundMenu.h"
#include <QContextMenuEvent>
#include "FluTemplateDemo.h"
#include "../controls/FluAction.h"
#include "../controls/FluLabel.h"

class FluRoundMenuDemo : public FluTemplateDemo
{
  public:
    FluRoundMenuDemo(QWidget* parent = nullptr);

  protected:
    void contextMenuEvent(QContextMenuEvent* event);

  private:
    FluLabel* m_label;
};
