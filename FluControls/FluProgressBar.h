#pragma once

#include <QProgressBar>
#include "../FluUtils/FluUtils.h"

class FluProgressBar : public QProgressBar
{
    Q_OBJECT
  public:
      FluProgressBar(QWidget* parent = nullptr) : QProgressBar(parent)
      {
          setTextVisible(true);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluProgressBar.qss", this);
      }

  protected:

};
