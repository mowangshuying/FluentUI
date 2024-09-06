#pragma once

#include "../FluUtils/FluUtils.h"
#include <QPushButton>

class FluStyleButton : public QPushButton
{
    Q_OBJECT
  public:
    FluStyleButton(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
