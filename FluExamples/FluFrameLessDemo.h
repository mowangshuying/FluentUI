#pragma once

#include "../FluControls/FluFrameLessWidget.h"
#include "../FluControls/FluRadioButton.h"
#include "../FluControls/FluToggleSwitch.h"
#include <QHBoxLayout>

class FluFrameLessDemo : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    FluFrameLessDemo(QWidget* parent = nullptr);

    //void paintEvent(QPaintEvent* event)
    //{
        // LOG_DEBUG << "themeSwitch:" << m_themeSwitch->isEnabled();
    //}

  protected:
    QHBoxLayout* m_hThemeSwitchLayout;
    FluToggleSwitch* m_themeSwitch;
};
