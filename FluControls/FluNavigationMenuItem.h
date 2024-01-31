#pragma once

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

#include "FluNavigationItem.h"
#include "../FluUtils/FluUtils.h"

class FluNavigationMenuItem : public FluNavigationItem
{
    Q_OBJECT
  public:
    FluNavigationMenuItem(QWidget *parent = nullptr);

  signals:
    void menuItemClicked();
  public slots:
      void onThemeChanged()
      {
          if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
          {
              // FluIconUtils::getFluentIcon(FluAwesomeType::GlobalNavButton)
              m_menuButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::GlobalNavButton, QColor(8, 8, 8)));
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNavigationMenuItem.qss", this);
          }
          else
          {
              m_menuButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::GlobalNavButton, QColor(239, 239, 239)));
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluNavigationMenuItem.qss", this);
          }
      }
  protected:
    QPushButton *m_menuButton;
    QHBoxLayout *m_hLayout;
};
