#pragma once

#include <QProgressBar>
#include "../Utils/FluUtils.h"

class FluProgressBar : public QProgressBar
{
    Q_OBJECT
  public:
    FluProgressBar(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();

  protected:
};
