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
    explicit FluRadioButton(QWidget* parent = nullptr) : QRadioButton(parent)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluRadioButton.qss", this);
    }

    explicit FluRadioButton(const QString& text, QWidget* parent = nullptr) : QRadioButton(text, parent)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluRadioButton.qss", this);
    }
};
