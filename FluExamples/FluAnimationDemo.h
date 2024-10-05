#pragma once

#include "FluTemplateDemo.h"
#include <QPropertyAnimation>
#include "../FluControls/FluPushButton.h"
#include "../FluUtils/FluUtils.h"
// #include <QState>
// #include <QStateMachine>

// QParallelAnimationGroup
// QSequentialAnimationGroup
class FluAnimationDemo : public FluTemplateDemo
{
  public:
    FluAnimationDemo(QWidget* parent = nullptr);

    void addPosAni();

    void addOpacityAni();

    void addShakeAni();

    // void addStateMachineAni();
};
