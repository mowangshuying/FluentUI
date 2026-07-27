#pragma once

#include "FluTemplateDemo.h"
#include <QSystemTrayIcon>
#include "../Controls/FluSystemTrayMenu.h"
#include "../Controls/FluSystemTrayIcon.h"

class FluSystemTrayIconDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluSystemTrayIconDemo(QWidget* parent = nullptr);

  protected:
    FluSystemTrayIcon* m_systemTrayIcon;
};
