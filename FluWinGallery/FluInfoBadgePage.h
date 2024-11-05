#pragma once

#include "../FluControls/FluInfoBarMgr.h"
#include "../FluControls/FluInfoBadge.h"
#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluInfoBadgePage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluInfoBadgePage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
