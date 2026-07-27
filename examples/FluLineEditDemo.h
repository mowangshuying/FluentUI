#pragma once

#include <QLineEdit>

#include "../Controls/FluLineEdit.h"
#include "FluDisplay16.h"
#include "../Controls/FluSearchLineEdit.h"
#include "../Controls/FluAutoSuggestBox.h"
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

class FluLineEditDemo : public FluDisplay16
{
    Q_OBJECT
  public:
    FluLineEditDemo(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* paintEvent);
};
