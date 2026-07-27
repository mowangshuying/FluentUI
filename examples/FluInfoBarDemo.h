#pragma once

#include "../Controls/FluShortInfoBar.h"
#include "../Controls/FluWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../Controls/FluPushButton.h"
#include "../Controls/FluInfoBarMgr.h"
#include "FluTemplateDemo.h"

class FluInfoBarDemo : public FluTemplateDemo
{
    // Q_OBJECT
  public:
    FluInfoBarDemo(QWidget* parent = nullptr);
};
