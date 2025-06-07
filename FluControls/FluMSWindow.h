#pragma once

#include "FluFrameLessWidget.h"
#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>

#include "FluMSNavigationView.h"
#include "FluStackedLayout.h"

class FluMSWindow : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    FluMSWindow(QWidget* parent = nullptr);

    void addWidget(FluAwesomeType awesomeType, QString text, QString key, QWidget* page, FluMSNavigationItemPosition position);

  public slots:
    void onThemeChanged();

  protected:
    FluMSNavigationView* m_navView;
    FluStackedLayout* m_sLayout;
};
