#pragma once

#include <QFrame>

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluGraphicalButton.h"
#include "../FluControls/FluStyleButton.h"
#include "../FluControls/FluDisplayBoxEx.h"
#include "../FluControls/FluCheckBox.h"

class FluButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
