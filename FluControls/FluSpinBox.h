#pragma once

#include "../FluUtils/FluUtils.h"
#include <QSpinBox>

class FluSpinBox : public QSpinBox
{
    Q_OBJECT
  public:
    FluSpinBox(QWidget* parent) : QSpinBox(parent)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSpinBox.qss", this);
    }
};
