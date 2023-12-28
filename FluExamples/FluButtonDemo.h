#pragma once

#include "../FluControls/FluPushButton.h"
#include <QPaintEvent>
#include <QStyleOption>
#include <QWidget>

class FluButtonDemo : public QWidget {
  Q_OBJECT
public:
  FluButtonDemo(QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *paintEvent);
};
