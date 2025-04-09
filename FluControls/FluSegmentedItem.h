#pragma once

#include <QPushButton>
#include "../FluUtils/FluUtils.h"

class FluSegmentedItem : public QPushButton
{
    Q_OBJECT
  public:
    FluSegmentedItem(QWidget* parent = nullptr);
  signals:
    void ItemClicked(FluSegmentedItem* item);
  public slots:
    void onThemeChanged();

  protected:
};
