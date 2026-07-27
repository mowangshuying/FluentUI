#pragma once

#include "../controls/FluFrameLessWidget.h"
#include "../controls/FluHNavigationView.h"

class FluHNavigationViewDemo : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    FluHNavigationViewDemo(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();

  protected:
    FluHNavigationView* m_navView;
    // QVBoxLayout* m_vMainLayout;
};
