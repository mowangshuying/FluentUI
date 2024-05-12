#pragma once

#include <QDoubleSpinBox>
#include "../FluUtils/FluUtils.h"

class FluDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
  public:
    FluDoubleSpinBox(QWidget* parent = nullptr) : QDoubleSpinBox(parent)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDoubleSpinBox.qss", this);
        
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDoubleSpinBox.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluDoubleSpinBox.qss", this);
        }
    }
};
