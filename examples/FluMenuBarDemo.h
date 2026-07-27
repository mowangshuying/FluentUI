#pragma once

#include "../controls/FluWidget.h"
#include <QMenuBar>
#include "../controls/FluMenu.h"
#include "../controls/FluMenuBar.h"
#include "../utils/FluStyleSheetUtils.h"
#include "FluTemplateDemo.h"
#include <QMenu>

class FluMenuBarDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluMenuBarDemo(QWidget* parent = nullptr);

    void normalMenuBar();
    void ppMenuBar0();
    void ppMenuBar1();
};
