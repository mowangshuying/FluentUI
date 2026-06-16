#pragma once

#include <QLineEdit>
#include "FluDef.h"
#include "../Utils/FluUtils.h"
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>

class FluLineEdit : public QLineEdit
{
    Q_OBJECT
  public:
    FluLineEdit(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);
  public slots:
    virtual void onThemeChanged();
};
