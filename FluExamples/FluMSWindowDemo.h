#pragma once

#include "../FluControls/FluMSWindow.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluMSNavigationItem.h"
#include "../FluControls/FluMenu.h"
#include "../FluControls/FluAction.h"
#include "../FluControls/FluLabel.h"

class FluMSPage : public FluWidget
{
    Q_OBJECT
  public:
      FluMSPage(QString text, QWidget* parent = nullptr)
      {
          auto hLayout = new QHBoxLayout;
          setLayout(hLayout);
          hLayout->setAlignment(Qt::AlignCenter);
          
          auto label = new FluLabel;
          label->setText(text);
          label->setLabelStyle(FluLabelStyle::SubTitleTextBlockStyle);
          hLayout->addWidget(label);

          connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=]() { 
              onThemeChanged();
          });

          onThemeChanged();
      }

      void paintEvent(QPaintEvent* event)
      {
          QStyleOption opt;
          opt.initFrom(this);
          QPainter painter(this);
          style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }
    public slots:
        void onThemeChanged()
        {
            if (FluThemeUtils::isLightTheme())
            {
                FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMSPage.qss", this);
            }
            else if (FluThemeUtils::isDarkTheme())
            {
                FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluMSPage.qss", this);
            }
        }
};

class FluMSWindowDemo : public FluMSWindow
{
    Q_OBJECT
  public:
      FluMSWindowDemo(QWidget* parent = nullptr) : FluMSWindow(parent)
      {
          auto homePage = new FluMSPage("Home Page");
          addWidget(FluAwesomeType::Home, "Home", "HomePage", homePage, FluMSNavigationItemPosition::Top);

          auto applicationPage = new FluMSPage("Application Page");
          addWidget(FluAwesomeType::OEM, "Application", "ApplicationPage", applicationPage, FluMSNavigationItemPosition::Top);

          auto gamePage = new FluMSPage("Game Page");
          addWidget(FluAwesomeType::Game, "Game", "GamePage", gamePage, FluMSNavigationItemPosition::Top);

          auto settingsPage = new FluMSPage("Settings Page");
          addWidget(FluAwesomeType::Settings, "Settings", "SettingsPage", settingsPage, FluMSNavigationItemPosition::Bottom);

          m_contextMenu = new FluMenu;
          auto lightAction = new FluAction;
          lightAction->setText("light");
          auto darkAction = new FluAction;
          darkAction->setText("dark");
          m_contextMenu->addAction(lightAction);
          m_contextMenu->addAction(darkAction);
          connect(lightAction, &FluAction::triggered, this, [=]() { FluThemeUtils::getUtils()->setTheme(FluTheme::Light); });
          connect(darkAction, &FluAction::triggered, this, [=]() { FluThemeUtils::getUtils()->setTheme(FluTheme::Dark); });
      }

      void contextMenuEvent(QContextMenuEvent* event)
      {
          m_contextMenu->exec(event->globalPos());
      }

    protected:
      FluMenu* m_contextMenu;
};
