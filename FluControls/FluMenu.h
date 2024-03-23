#pragma once

#include <QMenu>
#include "../FluUtils/FluUtils.h"
#include "FluAction.h"

class FluMenu : public QMenu
{
    Q_OBJECT
  public:
    FluMenu(QWidget* parent = nullptr);

    void addAction(FluAction* action);

    void mouseMoveEvent(QMouseEvent* e);

    void paintEvent(QPaintEvent* event);

  public slots:
    void onThemeChanged();
};
