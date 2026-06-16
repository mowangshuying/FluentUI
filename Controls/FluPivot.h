#pragma once

#include "FluWidget.h"
#include "FluStackedLayout.h"
#include <QVBoxLayout>
#include "FluPivotTitleBar.h"
#include "FluPivotTitleBarItem.h"
#include "FluStackedLayout.h"

class FluPivot : public FluWidget
{
    Q_OBJECT
  public:
    FluPivot(QWidget* parent = nullptr);

    void addPivotItem(QString key, QWidget* widget);

    void addPivotItem(FluPivotTitleBarItem* item, QWidget* widget);

  public slots:
    void pivotItemChanged(FluPivotTitleBarItem* item);

    void onThemeChanged();

  protected:
    QVBoxLayout* m_vMainLayout;
    FluPivotTitleBar* m_titleBar;
    FluStackedLayout* m_sLayout;
};
