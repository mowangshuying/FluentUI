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

    // auto item2411 = new FluHNavigationIconTextItem("The Other1--------xyz", item241);
    // auto item2412 = new FluHNavigationIconTextItem("The Other2--------xyzxyz", item241);
    // auto item2413 = new FluHNavigationIconTextItem("The Other3--------xyzxyzxyz", item241);

    item2->addItem(item21);
    item2->addItem(item22);
    item2->addItem(item23);
    item2->addItem(item24);

    item24->addItem(item241);
    item24->addItem(item242);
    item24->addItem(item243);

    // item241->addItem(item2411);
    //   item241->addItem(item2412);
    //  item241->addItem(item2413);

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
    auto item51 = new FluHNavigationIconTextItem("FlipView", item5);
    auto item52 = new FluHNavigationIconTextItem("ListView", item5);
    auto item53 = new FluHNavigationIconTextItem("TreeView", item5);

    item5->addItem(item51);
    item5->addItem(item52);
    item5->addItem(item53);

    m_hNavView->addItemToMidLayout(item5);

    auto item6 = new FluHNavigationIconTextItem(FluAwesomeType::Calendar, "Date & Time");

    auto item61 = new FluHNavigationIconTextItem("CalendarDatePicker", item6);
    auto item62 = new FluHNavigationIconTextItem("CalendarView", item6);
    auto item63 = new FluHNavigationIconTextItem("DatePicker", item6);
    auto item64 = new FluHNavigationIconTextItem("TimePicker", item6);

    item6->addItem(item61);
    item6->addItem(item62);
    item6->addItem(item63);
    item6->addItem(item64);

    m_hNavView->addItemToMidLayout(item6);

    auto item7 = new FluHNavigationIconTextItem(FluAwesomeType::Comment, "Dialogs & flyouts");

    auto item71 = new FluHNavigationIconTextItem("ContentDialog", item7);
    auto item72 = new FluHNavigationIconTextItem("Flyout", item7);
    auto item73 = new FluHNavigationIconTextItem("TeachingTip", item7);

    item7->addItem(item71);
    item7->addItem(item72);
    item7->addItem(item73);

    m_hNavView->addItemToMidLayout(item7);

    auto item8 = new FluHNavigationIconTextItem(FluAwesomeType::PreviewLink, "Layout");

    auto item81 = new FluHNavigationIconTextItem("Border", item8);
    auto item82 = new FluHNavigationIconTextItem("Canvas", item8);
    auto item83 = new FluHNavigationIconTextItem("Expander", item8);
    auto item84 = new FluHNavigationIconTextItem("ItemsRepeater", item8);
    auto item85 = new FluHNavigationIconTextItem("Grid", item8);
    auto item86 = new FluHNavigationIconTextItem("RadioButtons", item8);
    auto item87 = new FluHNavigationIconTextItem("RelativePanel", item8);
    auto item88 = new FluHNavigationIconTextItem("SplitView", item8);
    auto item89 = new FluHNavigationIconTextItem("StackPanel", item8);
    auto item810 = new FluHNavigationIconTextItem("VariableSizedWrapGrid", item8);
    auto item811 = new FluHNavigationIconTextItem("ViewBox", item8);

    item8->addItem(item81);
    item8->addItem(item82);
    item8->addItem(item83);
    item8->addItem(item84);
    item8->addItem(item85);
    item8->addItem(item86);
    item8->addItem(item87);
    item8->addItem(item88);
    item8->addItem(item89);
    item8->addItem(item810);
    item8->addItem(item811);

    m_hNavView->addItemToMidLayout(item8);

    auto item9 = new FluHNavigationIconTextItem(FluAwesomeType::Calendar, "Mendia");

    auto item91 = new FluHNavigationIconTextItem("AnimatedVisualPlayer", item9);
    auto item92 = new FluHNavigationIconTextItem("Capture Element / Camera Preview", item9);
    auto item93 = new FluHNavigationIconTextItem("Image", item9);
    auto item94 = new FluHNavigationIconTextItem("mediaPalyerElement", item9);
    auto item95 = new FluHNavigationIconTextItem("PersonPicture", item9);
    auto item96 = new FluHNavigationIconTextItem("Sound", item9);
    auto item97 = new FluHNavigationIconTextItem("WebView2", item9);

    item9->addItem(item91);
    item9->addItem(item92);
    item9->addItem(item93);
    item9->addItem(item94);
    item9->addItem(item95);
    item9->addItem(item96);
    item9->addItem(item97);

    m_hNavView->addItemToMidLayout(item9);

    auto item10 = new FluHNavigationIconTextItem(FluAwesomeType::Save, "Menu & toolbars");

    //  auto item101 = new FluHNavigationIconTextItem("XamlUICommand", item10);
    //  auto item102 = new FluHNavigationIconTextItem("StandardUICommand", item10);
    auto item103 = new FluHNavigationIconTextItem("AppBarButton", item10);
    auto item104 = new FluHNavigationIconTextItem("AppBarSeparator", item10);
    auto item105 = new FluHNavigationIconTextItem("AppBarToggleButton", item10);
    auto item106 = new FluHNavigationIconTextItem("CommandBar", item10);
    auto item107 = new FluHNavigationIconTextItem("MenuBar", item10);
    auto item108 = new FluHNavigationIconTextItem("CommandBarFlyout", item10);
    auto item109 = new FluHNavigationIconTextItem("MenuFlyout", item10);
    auto item1010 = new FluHNavigationIconTextItem("SwipeControl", item10);

    // item10->addItem(item101);
    // item10->addItem(item102);
    item10->addItem(item103);
    item10->addItem(item104);
    item10->addItem(item105);
    item10->addItem(item106);
    item10->addItem(item107);
    item10->addItem(item108);
    item10->addItem(item109);
    item10->addItem(item1010);

    m_hNavView->addItemToMidLayout(item10);

    auto item11 = new FluHNavigationIconTextItem(FluAwesomeType::BookmarksMirrored, "Navigation");

    auto item111 = new FluHNavigationIconTextItem("BreadcrumbBar", item11);
    auto item112 = new FluHNavigationIconTextItem("NavigationView", item11);
    auto item113 = new FluHNavigationIconTextItem("Pivot", item11);
    auto item114 = new FluHNavigationIconTextItem("TabView", item11);

    item11->addItem(item111);
    item11->addItem(item112);
    item11->addItem(item113);
    item11->addItem(item114);

    m_hNavView->addItemToMidLayout(item11);

    auto item12 = new FluHNavigationIconTextItem(FluAwesomeType::Sort, "Scrolling");

    auto item121 = new FluHNavigationIconTextItem("AnnotatedScrollBar", item12);
    auto item122 = new FluHNavigationIconTextItem("PipsPager", item12);
    auto item123 = new FluHNavigationIconTextItem("ScrollView", item12);
    auto item124 = new FluHNavigationIconTextItem("ScrollViewer", item12);
    auto item125 = new FluHNavigationIconTextItem("SemanticZoom", item12);

    item12->addItem(item121);
    item12->addItem(item122);
    item12->addItem(item123);
    item12->addItem(item124);
    item12->addItem(item125);

    m_hNavView->addItemToMidLayout(item12);

    auto item13 = new FluHNavigationIconTextItem(FluAwesomeType::Reminder, "Status & info");

    auto item131 = new FluHNavigationIconTextItem("InfoBadge", item13);
    auto item132 = new FluHNavigationIconTextItem("InfoBar", item13);
    auto item133 = new FluHNavigationIconTextItem("progressBar", item13);
    auto item134 = new FluHNavigationIconTextItem("progressRing", item13);
    auto item135 = new FluHNavigationIconTextItem("ToolTip", item13);

    item13->addItem(item131);
    item13->addItem(item132);
    item13->addItem(item133);
    item13->addItem(item134);
    item13->addItem(item135);

    m_hNavView->addItemToMidLayout(item13);

    auto item14 = new FluHNavigationIconTextItem(FluAwesomeType::Font, "Text");

    auto item141 = new FluHNavigationIconTextItem("AutoSuggestBox", item14);
    auto item142 = new FluHNavigationIconTextItem("NumberBox", item14);
    auto item143 = new FluHNavigationIconTextItem("PasswordBox", item14);
    auto item144 = new FluHNavigationIconTextItem("RichEditBox", item14);
    auto item145 = new FluHNavigationIconTextItem("RichTextBlock", item14);
    auto item146 = new FluHNavigationIconTextItem("TextBlock", item14);
    auto item147 = new FluHNavigationIconTextItem("TextBox", item14);

    item14->addItem(item141);
    item14->addItem(item142);
    item14->addItem(item143);
    item14->addItem(item144);
    item14->addItem(item145);
    item14->addItem(item146);
    item14->addItem(item147);

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
