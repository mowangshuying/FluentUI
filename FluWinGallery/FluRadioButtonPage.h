#pragma once

#include "../FluUtils/FluUtils.h"
#include "FluAEmptyPage.h"

class FluRadioButtonPage : public FluAEmptyPage 
{
  public:
      FluRadioButtonPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
      {
          m_mainLayout->setAlignment(Qt::AlignTop);
          m_titleLabel->setText("RadioButton");
          m_infoLabel->setText("Use RadioButton to let a user choose between mutually exclusive, related options. Generally contained within a RadioButtons group control.");
      }
};
