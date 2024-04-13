#pragma once

#include <QWidget>
#include "../FluControls/FluLoopView.h"
#include "../FluControls/FluTimePicker24HView.h"

#include "../FluControls/FluAmPmView.h"

class FluLoopViewDemo : public QWidget
{
    Q_OBJECT
  public:
    FluLoopViewDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        auto timePicker24HView = new FluTimePicker24HView(this);
        timePicker24HView->move(50, 50);

        auto amPmView = new FluAmPmView(80, this);
        amPmView->move(200, 50);
        amPmView->setFixedHeight(300);

        resize(800, 800);
    }
};
