#include "FluGalleryWindow.h"
#include "FluAEmptyPage.h"
#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>

FRAMELESSHELPER_USE_NAMESPACE

FluGalleryWindow::FluGalleryWindow(QWidget *parent /*= nullptr*/) : FluFrameLessWidget(parent)
{
    setWindowTitle("WinUi 3 Gallery - Cpp");
    setWindowIcon(QIcon("../res/Tiles/GalleryIcon.ico"));

    // resize
    resize(1200, 800);

    m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
    m_titleBar->setFixedHeight(48);

    QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluGalleryWindow.qss");
    setStyleSheet(qss);

    m_navView = new FluNavigationView(this);
    m_sLayout = new FluStackedLayout(this);

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
}
