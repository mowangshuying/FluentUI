#pragma once

#include "../FluUtils/FluUtils.h"
#include <QSpinBox>

class FluSpinBox : public QSpinBox
{
    Q_OBJECT
  public:
    FluSpinBox(QWidget* parent = nullptr) : QSpinBox(parent)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSpinBox.qss", this);
        
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSpinBox.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluSpinBox.qss", this);
        }
    }
};
