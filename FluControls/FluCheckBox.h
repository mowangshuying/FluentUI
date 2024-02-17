#pragma once

#include <QCheckBox>
#include "../FluUtils/FluUtils.h"

class FluCheckBox : public QCheckBox
{
    Q_OBJECT
  public:
    explicit FluCheckBox(QWidget* parent = nullptr) : QCheckBox(parent)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCheckBox.qss", this);
    }

    explicit FluCheckBox(const QString& text, QWidget* parent = nullptr) : QCheckBox(text, parent)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCheckBox.qss", this);
    }
};
