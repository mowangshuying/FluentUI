#pragma once

#include <QWidget>
#include <QLabel>
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluRoundMenu.h"
#include <QContextMenuEvent>
#include "FluTemplateDemo.h"
#include "../FluControls/FluAction.h"

class FluRoundMenuDemo : public FluTemplateDemo
{
  public:
    FluRoundMenuDemo(QWidget* parent = nullptr);

  protected:
    void contextMenuEvent(QContextMenuEvent* event);

  private:
    QLabel* m_label;
};
