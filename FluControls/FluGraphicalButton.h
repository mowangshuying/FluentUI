#pragma once

#include "../FluUtils/FluUtils.h"
#include "FluDef.h"
#include <QPushButton>

class FluGraphicalButton : public QPushButton
{
    Q_OBJECT
  public:
    FluGraphicalButton(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
