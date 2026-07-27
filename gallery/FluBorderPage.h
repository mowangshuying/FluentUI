#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluBorder.h"
#include "../controls/FluDisplayBoxEx.h"
#include "../controls/FluVRadioGroupBox.h"

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
