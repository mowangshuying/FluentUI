#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluBorder.h"
#include "../Controls/FluDisplayBoxEx.h"
#include "../Controls/FluVRadioGroupBox.h"

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
