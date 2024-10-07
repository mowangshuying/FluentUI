#pragma once

#include "../FluControls/FluWidget.h"
#include <QStackedLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QHBoxLayout>

class FluSlideWindowDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluSlideWindowDemo(QWidget* parent = nullptr);

    void slideIt()
    {
        // cur widget
        QPropertyAnimation* curAnimation = new QPropertyAnimation(m_page1, "pos");
        curAnimation->setDuration(500);
        curAnimation->setStartValue(QPoint(0, 0));
        curAnimation->setEndValue(QPoint(-width(), 0));
        curAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        // m_hLayout->setCurrentWidget(nextWidget);

        // next widget
        QPropertyAnimation* nextAnimation = new QPropertyAnimation(m_page2, "pos");
        nextAnimation->setDuration(500);
        nextAnimation->setStartValue(QPoint(width(), 0));
        nextAnimation->setEndValue(QPoint(0, 0));
        nextAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        // m_sLayout->setCurrentWidget(nextWidget);
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
        QWidget::mouseReleaseEvent(event);
        // emit clicked();
        slideIt();
    }

    // signals:
    //     void clicked();
  protected:
    QWidget* m_page1;
    QWidget* m_page2;
    QWidget* m_page3;
    // QStackedLayout* m_sLayout;
    QHBoxLayout* m_hLayout;
};
