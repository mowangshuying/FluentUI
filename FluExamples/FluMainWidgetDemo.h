#pragma once

#include "../FluControls/FluFrameLessWidget.h"

#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>

#include "../FluControls/FluMenuBar.h"
#include "../FluControls/FluAction.h"
#include "../FluControls/FluMenu.h"

class FluMainWidgetDemo : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    FluMainWidgetDemo(QWidget* parent = nullptr);

      void __initMenuBar();

    public slots:
      void onThemeChanged()
      {
          if (FluThemeUtils::isLightTheme())
          {
              m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
              m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
              m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
              m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
#ifndef Q_OS_MACOS
              m_titleBar->minimizeButton()->setActiveForegroundColor(Qt::black);
              m_titleBar->closeButton()->setActiveForegroundColor(Qt::black);
              m_titleBar->maximizeButton()->setActiveForegroundColor(Qt::black);
#endif
              m_titleBar->show();
          }
          else
          {
              m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
              m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
              m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::white);
              m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::white);

#ifndef Q_OS_MACOS
              m_titleBar->minimizeButton()->setActiveForegroundColor(Qt::white);
              m_titleBar->closeButton()->setActiveForegroundColor(Qt::white);
              m_titleBar->maximizeButton()->setActiveForegroundColor(Qt::white);
#endif
              m_titleBar->show();
          }
          FluStyleSheetUitls::setQssByFileName("FluMainWidgetDemo.qss", this, FluThemeUtils::getUtils()->getTheme());
      }
    protected:
      FluMenuBar* m_menuBar;
};
