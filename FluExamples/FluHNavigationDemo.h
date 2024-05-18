#pragma once

#include "../FluControls/FluFrameLessWidget.h"
#include "../FluControls/FluHNavigationView.h"

class FluHNavigationDemo : public FluFrameLessWidget
{
    Q_OBJECT
  public:
      FluHNavigationDemo(QWidget* parent = nullptr);

   public slots:
      void onThemeChanged();

   protected:
      FluHNavigationView* m_hNavView;
     //QVBoxLayout* m_vMainLayout;
};
