#pragma once

#include "FluTemplateDemo.h"
#include <QSystemTrayIcon>
#include "../FluControls/FluSystemTrayMenu.h"
#include "../FluControls/FluSystemTrayIcon.h"

class FluSystemTrayIconDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluSystemTrayIconDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
    {
        m_systemTrayIcon = new FluSystemTrayIcon(this);

        auto openMainUiAction = new FluAction("OpenMainUI");
        auto baseSettingsAction = new FluAction("BaseSettings");
        auto uiLockAction = new FluAction("UiLock");
        auto exitAction = new FluAction("Exit");

        QList<QAction*> actions;
        actions.append(openMainUiAction);
        actions.append(baseSettingsAction);
        actions.append(uiLockAction);
        actions.append(exitAction);

        m_systemTrayIcon->getSystemTrayMenu()->addActions(actions);
        m_systemTrayIcon->show();
    }

  protected:
    FluSystemTrayIcon* m_systemTrayIcon;
};
