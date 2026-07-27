#pragma once

#include <QLabel>
#include "../Utils/FluUtils.h"

class FluColorLabel : public QLabel
{
    Q_OBJECT
  public:
    FluColorLabel(QWidget* parent = nullptr) : QLabel(parent)
    {
        FluStyleSheetUtils::setQssByFileName("FluColorLabel.qss", this, FluThemeUtils::getUtils()->getTheme());
    }
};
