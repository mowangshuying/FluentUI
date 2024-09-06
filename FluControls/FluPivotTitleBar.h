#pragma once

#include "FluWidget.h"
#include <QHBoxLayout>
#include "FluPivotTitleBarItem.h"

class FluPivotTitleBar : public FluWidget
{
    Q_OBJECT
  public:
    FluPivotTitleBar(QWidget* parent = nullptr);

    void addTitleBarItem(FluPivotTitleBarItem* item);

    void setCurTitleBarItem(FluPivotTitleBarItem* titleBarItem);
  public slots:
    void onThemeChanged();

  protected:
    QHBoxLayout* m_hMainLayout;
};
