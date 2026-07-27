#pragma once

#include <QFrame>

#include "FluAEmptyPage.h"
#include "../utils/FluUtils.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluPushButton.h"
#include "../controls/FluGraphicalButton.h"
#include "../controls/FluStyleButton.h"
#include "../controls/FluDisplayBoxEx.h"
#include "../controls/FluCheckBox.h"

class FluButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
