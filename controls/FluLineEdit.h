#pragma once

#include <QLineEdit>
#include "FluDef.h"
#include "../utils/FluUtils.h"
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QContextMenuEvent>

class FluLineEdit : public QLineEdit
{
    Q_OBJECT
  public:
    FluLineEdit(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

  protected:
    void contextMenuEvent(QContextMenuEvent* event);

    void onThemeChanged();
};
