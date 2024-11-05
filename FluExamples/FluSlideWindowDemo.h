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

    void slideIt();

    void mouseReleaseEvent(QMouseEvent* event);

    // signals:
    //     void clicked();
  protected:
    QWidget* m_page1;
    QWidget* m_page2;
    QWidget* m_page3;
    // QStackedLayout* m_sLayout;
    QHBoxLayout* m_hLayout;
};
