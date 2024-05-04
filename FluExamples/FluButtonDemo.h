#pragma once

#include "../FluControls/FluPushButton.h"
#include <QPaintEvent>
#include <QStyleOption>
#include <QWidget>

#include "FluDisplay16.h"

class FluButtonDemo : public FluDisplay16
{
    Q_OBJECT
  public:
    FluButtonDemo(QWidget *parent = nullptr);

  protected:
    void paintEvent(QPaintEvent *paintEvent);
};
