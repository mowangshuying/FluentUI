#pragma once

#include <QHBoxLayout>
#include "../controls/FluWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QStyleOption>
#include <QPainter>

#include "../controls/FluExpander.h"
#include "../controls/FluPushButton.h"
#include "../controls/FluToggleButton.h"
#include "../controls/FluLabel.h"

class FluExpandDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluExpandDemo(QWidget* parent = nullptr);

    void addDemo0();

    void addDemo1();

    void addDemo2();

    void paintEvent(QPaintEvent* event);
};
