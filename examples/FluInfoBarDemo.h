#pragma once

#include "../controls/FluShortInfoBar.h"
#include "../controls/FluWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../controls/FluPushButton.h"
#include "../controls/FluInfoBarMgr.h"
#include "FluTemplateDemo.h"

class FluInfoBarDemo : public FluTemplateDemo
{
    // Q_OBJECT
  public:
    FluInfoBarDemo(QWidget* parent = nullptr);
};
