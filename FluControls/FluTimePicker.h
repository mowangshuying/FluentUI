#pragma once

#include <QWidget>
#include <QPushButton>

class FluTimePicker : public QWidget
{
    Q_OBJECT
  public:
    FluTimePicker(QWidget* parent = nullptr) : QWidget(parent)
    {
        setFixedSize(240, 30);
    }

  protected:
    QPushButton* m_hourBtn;
    QPushButton* m_minuteBtn;
};
