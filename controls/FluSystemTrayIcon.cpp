#include "FluSystemTrayIcon.h"

FluSystemTrayIcon::FluSystemTrayIcon(QWidget* parent) : QSystemTrayIcon(parent), m_menu(nullptr)
{
    setIcon(parent->windowIcon());
    m_menu = new FluSystemTrayMenu;

    // auto openMainUiAction = new FluAction("OpenMainUI");
    // auto baseSettingsAction = new FluAction("BaseSettings");
    // auto uiLockAction = new FluAction("UiLock");
    // auto exitAction = new FluAction("Exit");

    // QList<QAction*> actions;
    // actions.append(openMainUiAction);
    // actions.append(baseSettingsAction);
    // actions.append(uiLockAction);
    // actions.append(exitAction);

    // m_menu->addActions(actions);*/
    setContextMenu(m_menu);

    connect(this, &QSystemTrayIcon::activated, this, [=](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Context)
        {
            if (m_menu == nullptr)
                return;

            QPoint po = QCursor::pos();
            m_menu->exec(QPoint(po.x(), po.y() - m_menu->sizeHint().height()));
        }
    });
}

FluSystemTrayMenu* FluSystemTrayIcon::getSystemTrayMenu()
{
    return m_menu;
}
