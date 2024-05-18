#pragma once

#include "FluHNavigationItem.h"
#include <QHBoxLayout>
#include "FluRotationButton.h"

class FluHNavigationSettingsItem : public FluHNavigationItem
{
    Q_OBJECT
  public:
      FluHNavigationSettingsItem(QWidget* parent = nullptr) : FluHNavigationItem(parent)
      {
          m_hMainLayout = new QHBoxLayout;
          setLayout(m_hMainLayout);

          m_hMainLayout->setContentsMargins(0, 0, 0, 0);

          m_icon = new FluRotationButton(FluAwesomeType::Settings);
          m_icon->setIconSize(QSize(24, 24));
          m_icon->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Settings));

          m_hMainLayout->addWidget(m_icon);
      }

      FluHNavigationSettingsItem(FluAwesomeType awesomeType, QWidget* parent = nullptr)
          : FluHNavigationSettingsItem(parent)
      {
          m_awesomeType = awesomeType;
          m_icon->setAwesomeType(awesomeType);
      }

    protected:
      FluAwesomeType m_awesomeType;
      FluRotationButton* m_icon;
      QHBoxLayout* m_hMainLayout;
};
