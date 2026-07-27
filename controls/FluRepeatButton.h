#pragma once

#include <QPushButton>
#include "../Utils/FluUtils.h"

class FluRepeatButton : public QPushButton
{
    Q_OBJECT
  public:
    FluRepeatButton(QWidget* parent = nullptr);

    void setClickCount(int count);

    int getClickCount();

  signals:
    void clickedCountChanged(int clickCount);

  public slots:
    void onThemeChanged();

  private:
    int m_clickedCount;
};
