#include "FluGalleryWindow.h"

#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>

FRAMELESSHELPER_USE_NAMESPACE

FluGalleryWindow::FluGalleryWindow(QWidget* parent /*= nullptr*/) : FluFrameLessWidget(parent)
{
	setWindowTitle("WinUi 3 Gallery Dev");
	setWindowIcon(QIcon("../res/Tiles/GalleryIcon.ico"));

	m_titleBar->setStyleSheet("background-color: transparent;");
	m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
	m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
	m_titleBar->setFixedHeight(40);

	m_navView = new FluNavigationView(this);
	m_sLayout = new QStackedLayout(this);
	m_contentLayout->addWidget(m_navView);
	m_contentLayout->addLayout(m_sLayout, 1);

	auto homePage = new FluHomePage(this);
	m_sLayout->addWidget(homePage);


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
