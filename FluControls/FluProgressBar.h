#pragma once

#include <QProgressBar>
#include "../FluUtils/FluUtils.h"

class FluProgressBar : public QProgressBar
{
    Q_OBJECT
  public:
    FluProgressBar(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();

  protected:
};
