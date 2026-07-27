#pragma once

#include <QLineEdit>

#include "../controls/FluLineEdit.h"
#include "FluDisplay16.h"
#include "../controls/FluSearchLineEdit.h"
#include "../controls/FluAutoSuggestBox.h"
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
