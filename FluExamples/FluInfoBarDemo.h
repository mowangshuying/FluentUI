#pragma once

#include "../FluControls/FluShortInfoBar.h"
#include "../FluControls/FluWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluInfoBarMgr.h"
#include "FluTemplateDemo.h"

class FluInfoBarDemo : public FluTemplateDemo
{
    // Q_OBJECT
  public:
    FluInfoBarDemo(QWidget* parent = nullptr);
};
