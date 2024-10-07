#pragma once

#include <QLineEdit>

#include "../FluControls/FluLineEdit.h"
#include "FluDisplay16.h"
#include "../FluControls/FluSearchLineEdit.h"
#include "../FluControls/FluAutoSuggestBox.h"
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
