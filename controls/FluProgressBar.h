#pragma once

#include <QProgressBar>
#include "../utils/FluUtils.h"

class FluProgressBar : public QProgressBar
{
    Q_OBJECT
  public:
    FluProgressBar(QWidget* parent = nullptr);

  protected:
    void onThemeChanged();
};
