#include "FluTemplateDemo.h"

#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluHNavigationIconTextItem.h"
#include "../FluControls/FluHNavigationSearchItem.h"
#include "../FluControls/FluHNavigationSettingsItem.h"
#include <QContextMenuEvent>

FluTemplateDemo::FluTemplateDemo(QWidget* parent /*= nullptr*/) : FluFrameLessWidget(parent)
{
    setWindowTitle("CppQt WinUI3 Template Demo Dev");
#ifndef _DEBUG
    setWindowTitle("CppQt WinUI3 Template Demo");
#endif
    setWindowIcon(QIcon("../res/Tiles/GalleryIcon.ico"));
    m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
    m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
    m_titleBar->setFixedHeight(48);

    m_titleBar->setObjectName("titleBar");

    m_contextMenu = new FluMenu;
    auto lightAction = new FluAction;
    lightAction->setText("light");

    auto darkAction = new FluAction;
    darkAction->setText("dark");

    m_contextMenu->addAction(lightAction);
    m_contextMenu->addAction(darkAction);

    connect(lightAction, &FluAction::triggered, this, [=]() { FluThemeUtils::getUtils()->setTheme(FluTheme::Light); });

    connect(darkAction, &FluAction::triggered, this, [=]() { FluThemeUtils::getUtils()->setTheme(FluTheme::Dark); });

    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    onThemeChanged();
}

void FluTemplateDemo::contextMenuEvent(QContextMenuEvent* event)
{
    m_contextMenu->exec(event->globalPos());
}

void FluTemplateDemo::onThemeChanged()
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
        m_titleBar->show();
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTemplateDemo.qss", this);
    }
    else
    {
        m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::white);
        m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::white);
#ifndef Q_OS_MACOS
        m_titleBar->minimizeButton()->setActiveForegroundColor(Qt::white);
        m_titleBar->closeButton()->setActiveForegroundColor(Qt::white);
        m_titleBar->maximizeButton()->setActiveForegroundColor(Qt::white);
#endif
        m_titleBar->show();
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTemplateDemo.qss", this);
    }
}
