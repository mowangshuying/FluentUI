#pragma once

#include "../Controls/FluWidget.h"
#include "../Controls/FluComboBox.h"
#include "../Controls/FluComboBoxEx.h"
#include "../Controls/FluLabel.h"
#include "FluTemplateDemo.h"

class FluComboBoxDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluComboBoxDemo(QWidget* parent = nullptr);

  protected:
    FluComboBoxEx* m_basicCombo;
    FluComboBoxEx* m_placeholderCombo;
    FluComboBoxEx* m_programCombo;
    FluComboBoxEx* m_enableCombo;
    FluComboBoxEx* m_iconCombo;
    FluLabel* m_resultLabel;
    FluLabel* m_countLabel;
};
