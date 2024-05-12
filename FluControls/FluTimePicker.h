#pragma once

#include "FluWidget.h"
#include <QPushButton>

class FluTimePicker : public QWidget
{
    Q_OBJECT
  public:
    FluTimePicker(QWidget* parent = nullptr) : FluWidget(parent)
    {
        setFixedSize(240, 30);
    }

  protected:
    QPushButton* m_hourBtn;
    QPushButton* m_minuteBtn;
};
