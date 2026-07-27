#pragma once

#include "../controls/FluInfoBarMgr.h"
#include "../controls/FluInfoBadge.h"
#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"

class FluInfoBadgePage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluInfoBadgePage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
