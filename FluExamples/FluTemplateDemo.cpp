#include "FluTemplateDemo.h"

#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluHNavigationIconTextItem.h"
#include "../FluControls/FluHNavigationSearchItem.h"
#include "../FluControls/FluHNavigationSettingsItem.h"
#include "../FluControls/FluThemeButton.h"
#include <QContextMenuEvent>
#include "../FluControls/FluMenuBar.h"


FRAMELESSHELPER_USE_NAMESPACE
FluTemplateDemo::FluTemplateDemo(QWidget* parent /*= nullptr*/) : FluFrameLessWidget(parent)
{
    setWindowTitle("CppQt WinUI3 Template Demo Dev");
#ifndef _DEBUG
    setWindowTitle("CppQt WinUI3 Template Demo");
#endif

    setWindowIcon(QIcon("../res/Tiles/GalleryIcon.ico"));
#ifdef USE_QRC
    setWindowIcon(QIcon(":/res/Tiles/GalleryIcon.ico"));
#endif


    m_titleBar->setObjectName("titleBar");


#if !defined USE_WINDOWKIT_WIDGET
    m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
    m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
    m_titleBar->setFixedHeight(36);

#ifndef Q_OS_MACOS
    auto hLayout = (QHBoxLayout *)m_titleBar->layout();
    auto vLayout = (QVBoxLayout *)hLayout->itemAt(1)->layout();
    auto hButtonLayout = (QHBoxLayout *)vLayout->itemAt(0)->layout();
    auto themeButton = new FluThemeButton;
    hButtonLayout->insertWidget(0, themeButton);
    FramelessWidgetsHelper::get(this)->setHitTestVisible(themeButton);

    // add menuBar
    //auto menuBar = new FluMenuBar;
    //auto newFileAction = new FluAction("New");
    //auto openFileAction = new FluAction("Open");
    //auto saveFileAction = new FluAction("Save");
    //auto saveAsFileAction = new FluAction("Save As");
    //auto exitAction = new FluAction("Exit");

    //auto fileMenu = new FluMenu(menuBar);
    //fileMenu->addAction(newFileAction);
    //fileMenu->addAction(openFileAction);
    //fileMenu->addAction(saveFileAction);
    //fileMenu->addAction(saveAsFileAction);


#endif

#endif

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    // onThemeChanged();
}


void FluTemplateDemo::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
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
    }
    else if(FluThemeUtils::isDarkTheme () || FluThemeUtils::isAtomOneDarkTheme())
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
    }

    // just do stylesheet;
    FluStyleSheetUitls::setQssByFileName("FluTemplateDemo.qss", this, FluThemeUtils::getUtils()->getTheme());
}
