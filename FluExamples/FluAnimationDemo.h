#pragma once

#include "FluTemplateDemo.h"
#include <QPropertyAnimation>
#include "../FluControls/FluPushButton.h"
#include "../FluUtils/FluUtils.h"
// #include <QState>
// #include <QStateMachine>

class FluTmpAniObj : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float tmp READ getTmp WRITE setTmp)
  public:
    FluTmpAniObj(QObject* parent = nullptr) : QObject(parent)
    {
        m_tmp = 1;
    }

    void setTmp(float tmp)
    {
        //LOG_DEBUG << "Tmp = " << tmp;
        m_tmp = tmp;
    }

    float getTmp()
    {
        return m_tmp;
    }

  private:
    float m_tmp;
};

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

    void addTmpAni();
};
