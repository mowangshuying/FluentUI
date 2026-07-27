#pragma once

#include <QSystemTrayIcon>
#include <QWidget>
#include "FluSystemTrayMenu.h"

class FluSystemTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
  public:
    FluSystemTrayIcon(QWidget* parent = nullptr);

    FluSystemTrayMenu* getSystemTrayMenu();

  protected:
    FluSystemTrayMenu* m_menu;
};
