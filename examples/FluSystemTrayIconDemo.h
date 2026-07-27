#pragma once

#include "FluTemplateDemo.h"
#include <QSystemTrayIcon>
#include "../controls/FluSystemTrayMenu.h"
#include "../controls/FluSystemTrayIcon.h"

class FluSystemTrayIconDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluSystemTrayIconDemo(QWidget* parent = nullptr);

  protected:
    FluSystemTrayIcon* m_systemTrayIcon;
};
