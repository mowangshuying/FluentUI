#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluBorder.h"
#include "../FluControls/FluDisplayBoxEx.h"
#include "../FluControls/FluVRadioGroupBox.h"

class FluBorderPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluBorderPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();

  protected:
    FluBorder* m_border;
};
