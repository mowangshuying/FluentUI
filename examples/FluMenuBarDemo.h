#pragma once

#include "../Controls/FluWidget.h"
#include <QMenuBar>
#include "../Controls/FluMenu.h"
#include "../Controls/FluMenuBar.h"
#include "../Utils/FluStyleSheetUtils.h"
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
