#pragma once

#include <QMenu>
#include "../FluUtils/FluUtils.h"

class FluMenu : public QMenu
{
    Q_OBJECT
  public:
    FluMenu(QWidget* parent = nullptr);

    void addAction(QAction* action);

    void mouseMoveEvent(QMouseEvent* e);

    void paintEvent(QPaintEvent* event);
};
