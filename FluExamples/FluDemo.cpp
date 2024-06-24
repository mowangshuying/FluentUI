#include "FluDemo.h"

#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluHNavigationIconTextItem.h"
#include "../FluControls/FluHNavigationSearchItem.h"
#include "../FluControls/FluHNavigationSettingsItem.h"

FluDemo::FluDemo(QWidget* parent /*= nullptr*/)
{
    setWindowTitle("CppQt WinUI3 Demo Dev");
#ifndef _DEBUG
    setWindowTitle("CppQt WinUI3 Demo");
#endif
    setWindowIcon(QIcon("../res/Tiles/GalleryIcon.ico"));
    m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
    m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
    m_titleBar->setFixedHeight(48);
}

void FluDemo::onThemeChanged()
{
    if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
    {
        m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
        m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
#ifndef Q_OS_MACOS
        m_titleBar->minimizeButton()->setActiveForegroundColor(Qt::black);
        m_titleBar->closeButton()->setActiveForegroundColor(Qt::black);
        m_titleBar->maximizeButton()->setActiveForegroundColor(Qt::black);
#endif
        // m_titleBar->update();
        // m_titleBar->style()->polish(m_titleBar);
        m_titleBar->show();
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDemo.qss", this);
        // repaint();
        // QApplication::processEvents();
    }
    else
    {
        m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::white);
        m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::white);
        // m_titleBar->update();
        // m_titleBar->style()->polish(m_titleBar);
#ifndef Q_OS_MACOS
        m_titleBar->minimizeButton()->setActiveForegroundColor(Qt::white);
        m_titleBar->closeButton()->setActiveForegroundColor(Qt::white);
        m_titleBar->maximizeButton()->setActiveForegroundColor(Qt::white);
#endif
        m_titleBar->show();
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluDemo.qss", this);
        // repaint();
        // QApplication::processEvents();
    }
}
