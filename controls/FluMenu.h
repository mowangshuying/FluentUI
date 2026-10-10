#pragma once

#include <QMenu>
#include "../utils/FluUtils.h"
#include "FluAction.h"

class FluMenu : public QMenu
{
    Q_OBJECT
  public:
    FluMenu(QWidget* parent = nullptr);

    static FluMenu* fromStandardMenu(QMenu* standardMenu, QWidget* parent = nullptr);

    static void execStandardContextMenu(QWidget* widget, QMenu* standardMenu, const QPoint& globalPos);

    void addAction(FluAction* action);

    void mouseMoveEvent(QMouseEvent* e);

    void paintEvent(QPaintEvent* event);

  public slots:
    void onThemeChanged();
};
