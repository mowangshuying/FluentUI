#include "FluHNavigationDemo.h"

#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluHNavigationIconTextItem.h"
#include "../FluControls/FluHNavigationSearchItem.h"
#include "../FluControls/FluHNavigationSettingsItem.h"

#include <QLabel>
FluHNavigationDemo::FluHNavigationDemo(QWidget* parent /*= nullptr*/) : FluFrameLessWidget(parent)
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

    // new
    m_vMainLayout->setAlignment(Qt::AlignTop);
    m_hNavView = new FluHNavigationView;
    m_vMainLayout->insertWidget(1, m_hNavView, 0, Qt::AlignTop);

    // add home item;
    auto item1 = new FluHNavigationIconTextItem(FluAwesomeType::Home, "Home");
    m_hNavView->addItemToMidLayout(item1);

    // add Design items;
    auto item2 = new FluHNavigationIconTextItem(FluAwesomeType::Design, "Design guidance", this);
    auto item21 = new FluHNavigationIconTextItem(FluAwesomeType::FontSize, "Typography", item2);
    auto item22 = new FluHNavigationIconTextItem(FluAwesomeType::EmojiTabSymbols, "Icons", item2);
    auto item23 = new FluHNavigationIconTextItem(FluAwesomeType::Color, "Colors", item2);
    auto item24 = new FluHNavigationIconTextItem(FluAwesomeType::EaseOfAccess, "Accessibility", item2);
    auto item241 = new FluHNavigationIconTextItem("Screen reader support", item24);
    auto item242 = new FluHNavigationIconTextItem("Keyboard support", item24);
    auto item243 = new FluHNavigationIconTextItem("Color contrast", item24);

    item2->addItem(item21);
    item2->addItem(item22);
    item2->addItem(item23);
    item2->addItem(item24);

    item24->addItem(item241);
    item24->addItem(item242);
    item24->addItem(item243);

    m_hNavView->addItemToMidLayout(item2);

    // add All samples;
    auto item3 = new FluHNavigationIconTextItem(FluAwesomeType::AllApps, "All samples");
    m_hNavView->addItemToMidLayout(item3);

    // Basic inputs;
    auto item4 = new FluHNavigationIconTextItem(FluAwesomeType::CheckboxComposite, "Basic input");
    auto item41 = new FluHNavigationIconTextItem("Button", item4);
    auto item42 = new FluHNavigationIconTextItem("DropDownButton", item4);
    auto item43 = new FluHNavigationIconTextItem("HyperLinkButton", item4);
    auto item44 = new FluHNavigationIconTextItem("RepeatButton", item4);
    auto item45 = new FluHNavigationIconTextItem("ToggleButton", item4);
    auto item46 = new FluHNavigationIconTextItem("ToggleSplitButton", item4);
    auto item47 = new FluHNavigationIconTextItem("CheckBox", item4);
    auto item48 = new FluHNavigationIconTextItem("ColorPicker", item4);
    auto item49 = new FluHNavigationIconTextItem("ComboBox", item4);
    auto item410 = new FluHNavigationIconTextItem("RadioButton", item4);
    auto item411 = new FluHNavigationIconTextItem("RatingControl", item4);
    auto item412 = new FluHNavigationIconTextItem("Slider", item4);
    auto item413 = new FluHNavigationIconTextItem("ToggleSwitch", item4);

    item4->addItem(item41);
    item4->addItem(item42);
    item4->addItem(item43);
    item4->addItem(item44);

    item4->addItem(item45);
    item4->addItem(item46);
    item4->addItem(item47);
    item4->addItem(item48);

    item4->addItem(item49);
    item4->addItem(item410);
    item4->addItem(item411);
    item4->addItem(item412);
    item4->addItem(item413);

    m_hNavView->addItemToMidLayout(item4);

    // Connections;
    auto item5 = new FluHNavigationIconTextItem(FluAwesomeType::TiltDown, "Connections");
    m_hNavView->addItemToMidLayout(item5);

    auto item6 = new FluHNavigationIconTextItem(FluAwesomeType::Calendar, "Date & Time");
    m_hNavView->addItemToMidLayout(item6);

    auto item7 = new FluHNavigationIconTextItem(FluAwesomeType::Comment, "Dialogs & flyouts");
    m_hNavView->addItemToMidLayout(item7);

    auto item8 = new FluHNavigationIconTextItem(FluAwesomeType::PreviewLink, "Layout");
    m_hNavView->addItemToMidLayout(item8);

    auto item9 = new FluHNavigationIconTextItem(FluAwesomeType::Calendar, "Mendia");
    m_hNavView->addItemToMidLayout(item9);

    auto item10 = new FluHNavigationIconTextItem(FluAwesomeType::Save, "Menu & toolbars");
    m_hNavView->addItemToMidLayout(item10);

    auto item11 = new FluHNavigationIconTextItem(FluAwesomeType::BookmarksMirrored, "Navigation");
    m_hNavView->addItemToMidLayout(item11);

    auto item12 = new FluHNavigationIconTextItem(FluAwesomeType::Sort, "Scrolling");
    m_hNavView->addItemToMidLayout(item12);

    auto item13 = new FluHNavigationIconTextItem(FluAwesomeType::Reminder, "Status & info");
    m_hNavView->addItemToMidLayout(item13);

    auto item14 = new FluHNavigationIconTextItem(FluAwesomeType::Font, "Text");
    m_hNavView->addItemToMidLayout(item14);

    auto searchItem = new FluHNavigationSearchItem;
    searchItem->setFixedWidth(220);
    m_hNavView->addItemToRightLayout(searchItem);

    auto settingsItem = new FluHNavigationSettingsItem(FluAwesomeType::Settings);
    m_hNavView->addItemToRightLayout(settingsItem);

    auto bodyWidget = new QWidget;
    bodyWidget->setObjectName("bodyWidget");
    m_contentLayout->addWidget(bodyWidget);

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHNavigationDemo.qss", this);
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    resize(800, 600);
}

void FluHNavigationDemo::onThemeChanged()
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
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHNavigationDemo.qss", this);
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
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHNavigationDemo.qss", this);
        // repaint();
        // QApplication::processEvents();
    }
}
