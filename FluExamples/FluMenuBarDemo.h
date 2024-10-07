#pragma once

#include "../FluControls/FluWidget.h"
#include <QMenuBar>
#include "../FluControls/FluMenu.h"
#include "../FluControls/FluMenuBar.h"
#include "../FluUtils/FluStyleSheetUitls.h"
#include <QMenu>

class FluMenuBarDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluMenuBarDemo(QWidget* parent = nullptr);
};
