#pragma once

#include "../Controls/FluFrameLessWidget.h"
#include "../Controls/FluRadioButton.h"
#include "../Controls/FluToggleSwitch.h"
#include <QHBoxLayout>

class FluFrameLessDemo : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    FluFrameLessDemo(QWidget* parent = nullptr);

    // void paintEvent(QPaintEvent* event)
    //{
    //  LOG_DEBUG << "themeSwitch:" << m_themeSwitch->isEnabled();
    //}

  protected:
    QHBoxLayout* m_themeSwitchLayout;
    FluToggleSwitch* m_themeSwitch;
};
