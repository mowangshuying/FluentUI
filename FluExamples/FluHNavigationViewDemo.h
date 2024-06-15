#pragma once

#include "../FluControls/FluFrameLessWidget.h"
#include "../FluControls/FluHNavigationView.h"

class FluHNavigationViewDemo : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    FluHNavigationViewDemo(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();

  protected:
    FluHNavigationView* m_hNavView;
    // QVBoxLayout* m_vMainLayout;
};
