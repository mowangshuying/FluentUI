#pragma once

#include "../controls/FluWidget.h"
#include "../controls/FluComboBox.h"
#include "../controls/FluLabel.h"
#include "FluTemplateDemo.h"

class FluComboBoxDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluComboBoxDemo(QWidget* parent = nullptr);

  protected:
    FluComboBox* m_basicCombo;
    ///*  FluComboBox* m_placeholderCombo;
    //  FluComboBox* m_programCombo;
    //  FluComboBox* m_enableCombo;
    //  FluComboBox* m_iconCombo;
    //  FluLabel* m_resultLabel;
    //  FluLabel* m_countLabel;*/
};
