#pragma once

#include <QHBoxLayout>
#include "../Controls/FluWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QStyleOption>
#include <QPainter>

#include "../Controls/FluExpander.h"
#include "../Controls/FluPushButton.h"
#include "../Controls/FluToggleButton.h"
#include "../Controls/FluLabel.h"

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
