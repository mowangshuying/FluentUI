#include "FluGalleryWindow.h"
#include "FluAEmptyPage.h"
#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>
#include "../FluControls/FluMessageBox.h"

FRAMELESSHELPER_USE_NAMESPACE

FluGalleryWindow::FluGalleryWindow(QWidget *parent /*= nullptr*/) : FluFrameLessWidget(parent)
{
    setWindowTitle("CppQt WinUI3 Gallery Dev");

#ifndef _DEBUG
    setWindowTitle("CppQt WinUI3 Gallery");
#endif

    setWindowIcon(QIcon("../res/Tiles/GalleryIcon.ico"));

    // resize
    resize(1200, 800);

    m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
    m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
    m_titleBar->setFixedHeight(48);

    QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluGalleryWindow.qss");
    setStyleSheet(qss);

    m_navView = new FluNavigationView(this);
    m_sLayout = new FluStackedLayout;

    // if nav long will be short, short will be long after clicked it.
    // m_navView->onMenuItemClicked();

    m_contentLayout->addWidget(m_navView);
    //  m_contentLayout->addSpacing(20);
    m_contentLayout->addLayout(m_sLayout, 1);

    //  auto homePage = new FluHomePage(this);
    //  m_sLayout->addWidget(homePage);

    //  auto aEmptyPage = new FluAEmptyPage(this);
    //  m_sLayout->addWidget(aEmptyPage);

    // home
    makeHomeNavItem();

    // design guidance
    makeDesignGuidanceNavItem();

    // samples
    makeSamplesNavItem();

    // basic input
    makeBasicInputNavItem();

    // collections
    makeCollectionsNavItem();

    // date & time
    makDateTimeNavItem();

    // dialogs & flyouts
    makeDialogsFlyouts();

    // layout
    makeLayoutNavItem();

    // media
    makeMediaNavItem();

    // menus & toolbars
    makeMenuToolBarsNavItem();

    // navigation
    makeNavigationNavItem();

    // srolling

    makeScrollingNavItem();

    // status & info

    makeStatusInfoNavItem();

    // text
    makeTextNavItem();

    // settings
    makeSettingsNavItem();

    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });

   ///* connect(m_titleBar->closeButton(), &QPushButton::clicked, [=]() { FluMessageBox messageBox;
   //     messageBox.exec();
   // });*/
}

void FluGalleryWindow::onThemeChanged()
{
    if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
    {
        m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
        m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluGalleryWindow.qss", this);
    }
    else
    {
        m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::white);
        m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::white);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluGalleryWindow.qss", this);
    }
}
