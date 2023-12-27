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
	{
		FluNavigationItem* item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::Home), "Home", this);
		m_navView->addNavigationItemMid(item);
	}

	// design guidance
	{
		FluNavigationItem* item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::Design), "Design guidance", this);
		FluNavigationItem* item1 = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::FontSize), "Typography", item);
		FluNavigationItem* item2 = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::EmojiTabSymbols), "Icons", item);
		FluNavigationItem* item3 = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::Color), "Colors", item);
		FluNavigationItem* item4 = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::SetHistoryStatus2), "Accessibility", item);
		FluNavigationItem* item5 = new FluNavigationItem("Screen reader support", item4);
		FluNavigationItem* item6 = new FluNavigationItem("Keyboard support", item4);
		FluNavigationItem* item7 = new FluNavigationItem("Color contrast", item4);
		item->addChildItem(item1);
		item->addChildItem(item2);
		item->addChildItem(item3);
		item->addChildItem(item4);
		item4->addChildItem(item5);
		item4->addChildItem(item6);
		item4->addChildItem(item7);
		m_navView->addNavigationItemMid(item);
	}

	// samples
	{
		FluNavigationItem* item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::AllApps), "All samples", this);
		m_navView->addNavigationItemMid(item);
	}

	// basic input
	{
		FluNavigationItem* item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::CheckboxComposite), "Basic input", this);

		FluNavigationItem* item1 = new FluNavigationItem("InputValidation", item);
		FluNavigationItem* item2 = new FluNavigationItem("Button", item);
		FluNavigationItem* item3 = new FluNavigationItem("DropDownButton", item);

		FluNavigationItem* item4 = new FluNavigationItem("HyperLinkButton", item);
		FluNavigationItem* item5 = new FluNavigationItem("RepeatButton", item);
		FluNavigationItem* item6 = new FluNavigationItem("ToggleButton", item);

		FluNavigationItem* item7 = new FluNavigationItem("SplitButton", item);
		FluNavigationItem* item8 = new FluNavigationItem("ToggleSplitButton", item);
		FluNavigationItem* item9 = new FluNavigationItem("CheckBox", item);

		FluNavigationItem* item10 = new FluNavigationItem("CheckBox", item);
		FluNavigationItem* item11 = new FluNavigationItem("ComboBox", item);
		FluNavigationItem* item12 = new FluNavigationItem("RadioButton", item);

		FluNavigationItem* item13 = new FluNavigationItem("RatingControl", item);
		FluNavigationItem* item14 = new FluNavigationItem("Slider", item);
		FluNavigationItem* item15 = new FluNavigationItem("ToggleSwith", item);

		item->addChildItem(item1);
		item->addChildItem(item2);
		item->addChildItem(item3);
		item->addChildItem(item4);
		item->addChildItem(item5);
		item->addChildItem(item6);
		item->addChildItem(item7);
		item->addChildItem(item8);
		item->addChildItem(item9);
		item->addChildItem(item10);
		item->addChildItem(item11);
		item->addChildItem(item12);
		item->addChildItem(item13);
		item->addChildItem(item14);
		item->addChildItem(item15);
		m_navView->addNavigationItemMid(item);
	}

	// collections
	{

	}

	// date & time
	{

	}

	// dialogs & flyouts
	{

	}

	// layout
	{

	}

	// media
	{

	}

	// menus & toolbars

	// motion

	// navigation

	// srolling

	// status & info

	// styles

	// system

	// text

	// windowing

	// settings
}
