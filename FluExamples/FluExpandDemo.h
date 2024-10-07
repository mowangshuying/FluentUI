#pragma once

#include <QHBoxLayout>
#include "../FluControls/FluWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QStyleOption>
#include <QPainter>

#include "../FluControls/FluExpander.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluToggleButton.h"
#include "../FluControls/FluLabel.h"

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
