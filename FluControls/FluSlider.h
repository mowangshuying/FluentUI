#pragma once

#include <QSlider>

#include "../FluUtils/FluUtils.h"

class FluSlider : public QSlider
{
	Q_OBJECT
  public:
      FluSlider(QWidget* parent = nullptr) : QSlider(parent)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSlider.qss", this);
      }

      FluSlider(Qt::Orientation orientation, QWidget* parent = nullptr) : QSlider(orientation, parent)
      {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSlider.qss", this);
      }
};
