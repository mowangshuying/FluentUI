#pragma once

#include "FluTemplateDemo.h"
#include <QPropertyAnimation>
#include "../FluControls/FluPushButton.h"
#include "../FluUtils/FluUtils.h"
#include <QState>
#include <QStateMachine>

// QParallelAnimationGroup
// QSequentialAnimationGroup
class FluAnimationDemo : public FluTemplateDemo
{
  public:
      FluAnimationDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
      {
          addPosAni();

          addOpacityAni();

          addShakeAni();

          addStateMachineAni();
      }

      void addPosAni()
      {
          auto btn = new FluPushButton(this);
          btn->setText("Pos Ani");
          btn->setFixedWidth(138);
          btn->move(100, 100);

           auto animation = new QPropertyAnimation(btn, "pos", this);
          animation->setStartValue(QPoint(100, 100));
          animation->setKeyValueAt(0.5, QPoint(100, 500));
          animation->setEndValue(QPoint(100, 100));
          
          // animation total time.
          animation->setDuration(10000);

          // animation->setEasingCurve(QEasingCurve::OutBounce);
          animation->setEasingCurve(QEasingCurve::InCurve);
          connect(btn, &FluPushButton::clicked, [=]() {
              animation->start();
              //LOG_DEBUG << "Animation Start.";
          });

          connect(animation, &QPropertyAnimation::valueChanged, [=](QVariant value) {});
          //connect(animation, &QPropertyAnimation::finished, [=]() {
              //LOG_DEBUG << "Animation Finished.";
          //    animation->deleteLater();
          //});
      }

      void addOpacityAni()
      {
          auto animation = new QPropertyAnimation;
          animation->setPropertyName("windowOpacity");
          animation->setTargetObject(this);
          animation->setDuration(10000);

          animation->setKeyValueAt(0, 1);
          animation->setKeyValueAt(0.5, 0);
          animation->setKeyValueAt(1, 1);

          auto btn = new FluPushButton(this);
          btn->setText("Opacity Ani");
          btn->setFixedWidth(138);
          btn->move(300, 100);

          connect(btn, &FluPushButton::clicked, [=]() { 
              animation->start();
          });

          // connect(animation, &QPropertyAnimation::finished, [=]() {
          //    animation->deleteLater();
          //});
      }

      void addShakeAni()
      {
          auto animation = new QPropertyAnimation(this, "pos", this);
          animation->setStartValue(pos());
          animation->setKeyValueAt(0.2, pos() - QPoint(-3, 0));
          animation->setKeyValueAt(0.4, pos() - QPoint(3, 0));
          animation->setKeyValueAt(0.6, pos() - QPoint(0, -3));
          animation->setKeyValueAt(0.8, pos() - QPoint(0, 3));
          animation->setEndValue(pos());

          animation->setDuration(100);
          animation->setLoopCount(5);

         
          auto btn = new FluPushButton(this);
          btn->setText("Shake Ani");
          btn->setFixedWidth(138);
          btn->move(500, 100);

          connect(btn, &FluPushButton::clicked, [=]() { 
              
              animation->setStartValue(pos());
              animation->setKeyValueAt(0.2, pos() - QPoint(-3, 0));
              animation->setKeyValueAt(0.4, pos() - QPoint(3, 0));
              animation->setKeyValueAt(0.6, pos() - QPoint(0, -3));
              animation->setKeyValueAt(0.8, pos() - QPoint(0, 3));
              animation->setEndValue(pos());

              animation->start(); 
              });

          //connect(animation, &QPropertyAnimation::finished, [=]() { animation->deleteLater(); });
      }

      void addStateMachineAni()
      {
          auto btn = new FluPushButton(this);
          //btn->setText("Click me!");
          btn->setFixedWidth(138);
          btn->move(100, 200);

          QState* state1 = new QState;
          state1->assignProperty(btn, "text", "@@@@");

          QState* state2 = new QState;
          state2->assignProperty(btn, "text", "%%%%");

          QState* state3 = new QState;
          state3->assignProperty(btn, "text", "&&&&&&&&");

          state1->addTransition(btn, &FluPushButton::clicked, state2);
          state2->addTransition(btn, &FluPushButton::clicked, state3);
          state3->addTransition(btn, &FluPushButton::clicked, state1);


          QStateMachine* stateMachine = new QStateMachine(this);
          stateMachine->addState(state1);
          stateMachine->addState(state2);
          stateMachine->addState(state3);

          stateMachine->setInitialState(state1);
          stateMachine->start();
      }
};
