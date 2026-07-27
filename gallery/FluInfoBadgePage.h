#pragma once

#include "../Controls/FluInfoBarMgr.h"
#include "../Controls/FluInfoBadge.h"
#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"

class FluInfoBadgePage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluInfoBadgePage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
