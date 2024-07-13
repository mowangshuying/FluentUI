#pragma once

#include "FluExpander.h"
#include "../FluUtils/FluUtils.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

class FluSettingsVersionBox : public FluExpander
{
    Q_OBJECT
  public:
      FluSettingsVersionBox(QWidget* parent = nullptr);

      QLabel* getTitleLabel()
      {
          return m_titleLabel;
      }

      QLabel* getInfoLabel()
      {
          return m_infoLabel;
      }

      QLabel* getVersionLabel()
      {
          return m_versionLabel;
      }

      QLabel* getIconLabel()
      {
          return m_iconLabel;
      }

  protected:
      FluAwesomeType m_iconAwesomeType;
      QVBoxLayout* m_vLayout;

      QLabel* m_iconLabel;
      QLabel* m_titleLabel;
      QLabel* m_infoLabel;
      QLabel* m_versionLabel;
};
