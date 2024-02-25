#pragma once

#include <QWidget>
#include "../FluControls/FluCalendarView.h"
#include "../FluControls/FluCalendarDef.h"

class FluCalendarViewDemo : public QWidget
{
    Q_OBJECT
  public:
    FluCalendarViewDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        auto calendarView = new FluCalendarView(this);
        calendarView->move(50, 50);
        resize(600, 600);
    }
};
