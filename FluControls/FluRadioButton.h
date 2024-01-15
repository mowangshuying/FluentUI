#pragma once

#include <QRadioButton>
#include "../FluUtils/FluUtils.h"
#include <QProxyStyle>
#include <QPainter>
#include <QStyleOptionButton>

class FluRadioButton : public QRadioButton
{
    Q_OBJECT
  public:
    FluRadioButton(QWidget* parent = nullptr) : QRadioButton(parent)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluRadioButton.qss", this);
    }
};
