#pragma once

#include "../utils/FluStyleSheetUtils.h"
#include "../utils/FluThemeUtils.h"
#include <QTableWidget>

class FluTabWidget : public QTabWidget
{
    Q_OBJECT
  public:
    FluTabWidget(QWidget *parent = nullptr);

  public slots:
    void onThemeChanged();
};
