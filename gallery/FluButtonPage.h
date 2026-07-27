#pragma once

#include <QFrame>

#include "FluAEmptyPage.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluPushButton.h"
#include "../Controls/FluGraphicalButton.h"
#include "../Controls/FluStyleButton.h"
#include "../Controls/FluDisplayBoxEx.h"
#include "../Controls/FluCheckBox.h"

class FluButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
