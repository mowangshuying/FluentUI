#include "FluGalleryWindow.h"
#include "FluAEmptyPage.h"
#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>
#include "../controls/FluMessageBox.h"
#include <QApplication>
#include <QTimer>
#include "../controls/FluThemeButton.h"
#include "FluEmoijsPage.h"
#include "../utils/FluConfigUtils.h"

FRAMELESSHELPER_USE_NAMESPACE

#if !defined USE_WINDOWKIT_WIDGET
FluGalleryWindow::FluGalleryWindow(QWidget *parent /*= nullptr*/) : FluFrameLessWidget(parent)
#else
FluGalleryWindow::FluGalleryWindow(QWidget *parent /*= nullptr*/) : FluWindowKitWidget(parent)
#endif
{
    setWindowTitle(tr("CppQt WinUI3 Gallery Dev"));

#ifndef _DEBUG
    setWindowTitle(tr("CppQt WinUI3 Gallery"));
#endif

#ifndef USE_QRC
    setWindowIcon(QIcon("../res/Tiles/GalleryIcon.ico"));
#else
    setWindowIcon(QIcon(":/res/Tiles/GalleryIcon.ico"));
#endif

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

    connect(themeButton, &FluThemeButton::clickedThemeButton, this, [=]() {
        auto settingsPages = (FluSettingPage *)m_layout->getWidget("SettingPage");
        settingsPages->updateThemeSelectBox();
    });
#endif

#endif

    // QString qss = FluStyleSheetUtils::getQssByFileName("../stylesheet/light/FluGalleryWindow.qss");
    // setStyleSheet(qss);

    // 先读取导航样式配置
    int navStyle = FluConfigUtils::getUtils()->getNavStyle();
    m_isHorizontalNav = (navStyle == 1);

    m_navView = new FluVNavigationView(this);
    m_layout = new FluStackedLayout;

    m_contentLayout->addWidget(m_navView);
    m_contentLayout->addLayout(m_layout, 1);

    m_hNavView = new FluHNavigationView(this);
    m_hNavView->setObjectName("horizontalNavView");
    m_mainLayout->insertWidget(1, m_hNavView);
    
    if (m_isHorizontalNav) {
        m_navView->hide();
        m_hNavView->show();
    } else {
        m_navView->show();
        m_hNavView->hide();
    }

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

    m_navView->updateSearchKeys();

    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    connect(m_navView, &FluVNavigationView::searchKeyChanged, this, [=](QString text) { m_layout->setCurrentWidget(text); });
    connect(m_navView, &FluVNavigationView::keyChanged, this, [=](QString key) { m_layout->setCurrentWidget(key); });
    connect(m_hNavView, &FluHNavigationView::keyChanged, this, [=](QString key) { m_layout->setCurrentWidget(key); });

    auto settingsPage = (FluSettingPage *)m_layout->getWidget("SettingPage");
    if (settingsPage) {
        connect(settingsPage, &FluSettingPage::navigationStyleChanged, this, &FluGalleryWindow::switchNavigationStyle);
    }

#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
    FluThemeUtils::getUtils()->setTheme(FluTheme::Light);
    QTimer::singleShot(500, [=]() { m_navView->onThemeChanged(); });
#endif

    resize(1200, 900);
    setMinimumWidth(850);
    int navWidth = FluConfigUtils::getUtils()->getNavWidth();
    m_navView->setViewWidth(navWidth > 0 ? navWidth : 300);
    m_navView->setOnlyCollapseView(false);

    if (!m_isHorizontalNav && FluConfigUtils::getUtils()->getViewCollapsed())
        m_navView->collapseView();

    onThemeChanged();
}

void FluGalleryWindow::makeHNavigationGroup(FluAwesomeType type, QString text, std::vector<QPair<QString, QString>> items)
{
    auto parent = new FluHNavigationIconTextItem(type, text, m_hNavView);
    m_hNavView->addItemToLayout(parent, FluHNavigationItemPosition::Mid);
    for (auto& pair : items)
    {
        auto child = new FluHNavigationIconTextItem(pair.first, parent);
        child->setKey(pair.second);
        parent->addItem(child);
        connect(child, &FluHNavigationIconTextItem::itemClicked, this, [=]() {
            m_layout->setCurrentWidget(pair.second);
        });
    }
}



void FluGalleryWindow::makeHNavigationItem(FluAwesomeType type, QString text, QString key)
{
    auto item = new FluHNavigationIconTextItem(type, text, m_hNavView);
    item->setKey(key);
    m_hNavView->addItemToLayout(item, FluHNavigationItemPosition::Mid);
    connect(item, &FluHNavigationIconTextItem::itemClicked, this, [=]() {
        m_layout->setCurrentWidget(key);
    });
}

void FluGalleryWindow::animateNavSwitch(bool toHorizontal)
{
    setProperty("horizontalNav", toHorizontal);
    style()->polish(this);

    // toggle page borders via property
    for (int i = 0; i < m_layout->count(); i++)
    {
        QWidget *page = m_layout->widget(i);
        if (page)
        {
            page->setProperty("noBorder", toHorizontal);
            page->style()->polish(page);
        }
    }

    if (toHorizontal)
    {
        m_navView->setFixedWidth(m_navView->width());
        auto vAnim = new QPropertyAnimation(m_navView, "maximumWidth", this);
        vAnim->setDuration(200);
        vAnim->setEasingCurve(QEasingCurve::OutCubic);
        vAnim->setStartValue(m_navView->width());
        vAnim->setEndValue(0);
        connect(vAnim, &QPropertyAnimation::finished, this, [=]() {
            m_navView->setVisible(false);
            m_navView->setMaximumWidth(QWIDGETSIZE_MAX);
        });
        vAnim->start(QAbstractAnimation::DeleteWhenStopped);

        m_hNavView->setFixedHeight(0);
        m_hNavView->setMaximumHeight(0);
        m_hNavView->setVisible(true);
        auto hAnim = new QPropertyAnimation(m_hNavView, "maximumHeight", this);
        hAnim->setDuration(200);
        hAnim->setEasingCurve(QEasingCurve::OutCubic);
        hAnim->setStartValue(0);
        hAnim->setEndValue(40);
        connect(hAnim, &QPropertyAnimation::valueChanged, this, [=]() {
            m_hNavView->setFixedHeight(m_hNavView->maximumHeight());
        });
        hAnim->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else
    {
        m_navView->setFixedWidth(0);
        m_navView->setVisible(true);
        auto vAnim = new QPropertyAnimation(m_navView, "maximumWidth", this);
        vAnim->setDuration(200);
        vAnim->setEasingCurve(QEasingCurve::OutCubic);
        vAnim->setStartValue(0);

        ///
        vAnim->setEndValue(m_navView->calcViewWidthByIsLong());
        connect(vAnim, &QPropertyAnimation::finished, this, [=]() {
            m_navView->setMaximumWidth(QWIDGETSIZE_MAX);
            m_navView->setFixedWidth(m_navView->calcViewWidthByIsLong());
        });
        vAnim->start(QAbstractAnimation::DeleteWhenStopped);

        auto hAnim = new QPropertyAnimation(m_hNavView, "maximumHeight", this);
        hAnim->setDuration(200);
        hAnim->setEasingCurve(QEasingCurve::OutCubic);
        hAnim->setStartValue(40);
        hAnim->setEndValue(0);
        connect(hAnim, &QPropertyAnimation::valueChanged, this, [=]() {
            m_hNavView->setFixedHeight(m_hNavView->maximumHeight());
        });
        connect(hAnim, &QPropertyAnimation::finished, this, [=]() {
            m_hNavView->setVisible(false);
            m_hNavView->setMaximumHeight(40);
            m_hNavView->setFixedHeight(40);
        });
        hAnim->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void FluGalleryWindow::switchNavigationStyle(int index)
{
    m_isHorizontalNav = (index == 1);
    animateNavSwitch(m_isHorizontalNav);

    // 立即持久化导航样式
    FluConfigUtils::getUtils()->setNavStyle(m_isHorizontalNav ? 1 : 0);
}

void FluGalleryWindow::makeHomeNavItem()
{
    m_navView->insertIconTextItem(FluAwesomeType::Home, tr("Home"), "HomePage");

    auto homePage = new FluHomePage;
    m_layout->addWidget("HomePage", homePage);

    connect(homePage, &FluHomePage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);

    makeHNavigationItem(FluAwesomeType::Home, tr("Home"), "HomePage");
}

void FluGalleryWindow::makeDesignGuidanceNavItem()
{
    m_navView->insertIconTextItem(FluAwesomeType::Design, tr("Design guidance"), "DesignGuidancePage");
    m_navView->insertIconTextItem(FluAwesomeType::FontSize, tr("Typography"), "TypographyPage", "DesignGuidancePage");
    m_navView->insertIconTextItem(FluAwesomeType::EmojiTabSymbols, tr("Icons"), "IconsPage", "DesignGuidancePage");
    m_navView->insertIconTextItem(FluAwesomeType::Emoji, tr("Emoijs"), "EmoijsPage", "DesignGuidancePage");

    m_navView->insertIconTextItem(FluAwesomeType::Airplane, tr("2.level"), "2.levelPage", "DesignGuidancePage");

    m_navView->insertIconTextItem(FluAwesomeType::Airplane, tr("3.level1"), "3.level1Page", "2.levelPage");
    m_navView->insertIconTextItem(FluAwesomeType::Airplane, tr("3.level2"), "3.level2Page", "2.levelPage");
    m_navView->insertIconTextItem(FluAwesomeType::Airplane, tr("3.level3"), "3.level3Page", "2.levelPage");

    m_navView->insertIconTextItem(FluAwesomeType::Airplane, tr("4.level1"), "4.level1Page", "3.level1Page");
    m_navView->insertIconTextItem(FluAwesomeType::Airplane, tr("4.level2"), "4.level2Page", "3.level1Page");
    m_navView->insertIconTextItem(FluAwesomeType::Airplane, tr("4.level3"), "4.level3Page", "3.level1Page");

    m_navView->insertIconTextItem(FluAwesomeType::Airplane, tr("5.level1"), "5.level1Page", "4.level3Page");
    m_navView->insertIconTextItem(FluAwesomeType::Airplane, tr("5.level2"), "5.level2Page", "4.level3Page");
    m_navView->insertIconTextItem(FluAwesomeType::Airplane, tr("5.level3"), "5.level3Page", "4.level3Page");
    m_navView->insertIconTextItem(FluAwesomeType::Airplane, tr("5.level4"), "5.level4Page", "4.level3Page");

    auto typographyPage = new FluTypeographyPage;
    m_layout->addWidget("TypographyPage", typographyPage);

    auto iconsPage = new FluIconsPage;
    m_layout->addWidget("IconsPage", iconsPage);

    auto emoijsPage = new FluEmoijsPage;
    m_layout->addWidget("EmoijsPage", emoijsPage);
}

void FluGalleryWindow::makeSamplesNavItem()
{
    m_navView->insertIconTextItem(FluAwesomeType::AllApps, tr("All samples"), "AllSamplesPage");

    auto allSamplesPage = new FluAllSamplesPage;
    m_layout->addWidget("AllSamplesPage", allSamplesPage);

    connect(allSamplesPage, &FluAllSamplesPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);

    makeHNavigationItem(FluAwesomeType::AllApps, tr("All samples"), "AllSamplesPage");
}

void FluGalleryWindow::makeBasicInputNavItem()
{
    m_navView->insertIconTextItem(FluAwesomeType::CheckboxComposite, tr("Basic input"), "BasicInputPage");
    auto basicInputPage = new FluBasicInputPage;
    m_layout->addWidget("BasicInputPage", basicInputPage);

    auto *inputValidation = m_navView->insertIconTextItem(FluAwesomeType::None, tr("InputValidation"), "InputValidation", "BasicInputPage");
    inputValidation->enableThisItem(false);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("Button"), "ButtonPage", "BasicInputPage");
    m_layout->addWidget("ButtonPage", new FluButtonPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("DropDownButton"), "DropDownButtonPage", "BasicInputPage");
    m_layout->addWidget("DropDownButtonPage", new FluDropDownButtonPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("HyperLinkButton"), "HyperLinkButtonPage", "BasicInputPage");
    m_layout->addWidget("HyperLinkButtonPage", new FluHyperLinkButtonPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("RepeatButton"), "RepeatButtonPage", "BasicInputPage");
    m_layout->addWidget("RepeatButtonPage", new FluRepeatButtonPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("ToggleButton"), "ToggleButtonPage", "BasicInputPage");
    m_layout->addWidget("ToggleButtonPage", new FluToggleButtonPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("SplitButton"), "SplitButtonPage", "BasicInputPage");
    m_layout->addWidget("SplitButtonPage", new FluSplitButtonPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("ToggleSplitButton"), "ToggleSplitButton", "BasicInputPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("CheckBox"), "CheckBoxPage", "BasicInputPage");
    m_layout->addWidget("CheckBoxPage", new FluCheckBoxPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("ColorPicker"), "ColorPickerPage", "BasicInputPage");
    m_layout->addWidget("ColorPickerPage", new FluColorPickerPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("ComboBox"), "ComboBoxPage", "BasicInputPage");
    m_layout->addWidget("ComboBoxPage", new FluComboBoxPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("RadioButton"), "RadioButtonPage", "BasicInputPage");
    m_layout->addWidget("RadioButtonPage", new FluRadioButtonPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("RatingControl"), "RatingControlPage", "BasicInputPage");
    m_layout->addWidget("RatingControlPage", new FluRatingControlPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("Slider"), "SliderPage", "BasicInputPage");
    m_layout->addWidget("SliderPage", new FluSliderPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("ToggleSwitch"), "ToggleSwitchPage", "BasicInputPage");
    m_layout->addWidget("ToggleSwitchPage", new FluToggleSwitchPage);

    connect(basicInputPage, &FluBasicInputPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);

    makeHNavigationGroup(FluAwesomeType::CheckboxComposite, tr("Basic input"), {
        {tr("InputValidation"), ""}, {tr("Button"), "ButtonPage"}, {tr("DropDownButton"), "DropDownButtonPage"},
        {tr("HyperLinkButton"), "HyperLinkButtonPage"}, {tr("RepeatButton"), "RepeatButtonPage"},
        {tr("ToggleButton"), "ToggleButtonPage"}, {tr("SplitButton"), "SplitButtonPage"},
        {tr("ToggleSplitButton"), ""}, {tr("CheckBox"), "CheckBoxPage"}, {tr("ColorPicker"), "ColorPickerPage"},
        {tr("ComboBox"), "ComboBoxPage"}, {tr("RadioButton"), "RadioButtonPage"},
        {tr("RatingControl"), "RatingControlPage"}, {tr("Slider"), "SliderPage"},
        {tr("ToggleSwitch"), "ToggleSwitchPage"}
    });
}

void FluGalleryWindow::makeCollectionsNavItem()
{
    m_navView->insertIconTextItem(FluAwesomeType::TiltDown, tr("Connections"), "CollectionsPage");
    auto collectionsPage = new FluCollectionsPage;
    m_layout->addWidget("CollectionsPage", collectionsPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("FlipView"), "FlipViewPage", "CollectionsPage");
    m_layout->addWidget("FlipViewPage", new FluFlipViewPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("ListView"), "ListViewPage", "CollectionsPage");
    m_layout->addWidget("ListViewPage", new FluListViewPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("TreeView"), "TreeViewPage", "CollectionsPage");
    m_layout->addWidget("TreeViewPage", new FluTreeViewPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("TableView"), "TableViewPage", "CollectionsPage");
    m_layout->addWidget("TableViewPage", new FluTableViewPage);

    connect(collectionsPage, &FluCollectionsPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);

    makeHNavigationGroup(FluAwesomeType::TiltDown, tr("Connections"), {
        {tr("FlipView"), "FlipViewPage"}, {tr("ListView"), "ListViewPage"},
        {tr("TreeView"), "TreeViewPage"}, {tr("TableView"), "TableViewPage"}
    });
}

void FluGalleryWindow::makDateTimeNavItem()
{
    m_navView->insertIconTextItem(FluAwesomeType::Calendar, tr("Date & time"), "DateAndTimePage");
    auto dateAndTimePage = new FluDateAndTimePage;
    m_layout->addWidget("DateAndTimePage", dateAndTimePage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("CalendarDatePicker"), "CalendarDatePickerPage", "DateAndTimePage");
    m_layout->addWidget("CalendarDatePickerPage", new FluCalendarDatePickerPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("CalendarView"), "CalendarViewPage", "DateAndTimePage");
    m_layout->addWidget("CalendarViewPage", new FluCalendarViewPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("DatePicker"), "DatePickerPage", "DateAndTimePage");
    m_layout->addWidget("DatePickerPage", new FluDatePickerPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("TimePicker"), "TimePickerPage", "DateAndTimePage");
    m_layout->addWidget("TimePickerPage", new FluTimePickerPage);

    connect(dateAndTimePage, &FluDateAndTimePage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);

    makeHNavigationGroup(FluAwesomeType::Calendar, tr("Date & time"), {
        {tr("CalendarDatePicker"), "CalendarDatePickerPage"}, {tr("CalendarView"), "CalendarViewPage"},
        {tr("DatePicker"), "DatePickerPage"}, {tr("TimePicker"), "TimePickerPage"}
    });
}

void FluGalleryWindow::makeDialogsFlyouts()
{
    m_navView->insertIconTextItem(FluAwesomeType::Comment, tr("Dialogs & flyouts"), "DialogsAndFlyoutsPage");
    auto dialogAndFlyoutPage = new FluDialogsAndFlyoutsPage;
    m_layout->addWidget("DialogsAndFlyoutsPage", dialogAndFlyoutPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("ContentDialog"), "ContentDialogPage", "DialogsAndFlyoutsPage");
    m_layout->addWidget("ContentDialogPage", new FluContentDialogPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("Flyout"), "FlyoutPage", "DialogsAndFlyoutsPage");
    m_layout->addWidget("FlyoutPage", new FluFlyoutPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("TeachingTip"), "TeachingTipPage", "DialogsAndFlyoutsPage");

    connect(dialogAndFlyoutPage, &FluDialogsAndFlyoutsPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);

    makeHNavigationGroup(FluAwesomeType::Comment, tr("Dialogs & flyouts"), {
        {tr("ContentDialog"), "ContentDialogPage"}, {tr("Flyout"), "FlyoutPage"},
        {tr("TeachingTip"), "TeachingTipPage"}
    });
}

void FluGalleryWindow::makeLayoutNavItem()
{
    m_navView->insertIconTextItem(FluAwesomeType::PreviewLink, tr("Layout"), "LayoutPage");
    auto layoutPage = new FluLayoutPage;
    m_layout->addWidget("LayoutPage", layoutPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("Border"), "BorderPage", "LayoutPage");
    m_layout->addWidget("BorderPage", new FluBorderPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("Canvas"), "CanvasPage", "LayoutPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("Expander"), "ExpanderPage", "LayoutPage");
    m_layout->addWidget("ExpanderPage", new FluExpanderPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("ItemsRepeater"), "ItemsRepeaterPage", "LayoutPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("Grid"), "GridPage", "LayoutPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("RadioButtons"), "RadioButtonsPage", "LayoutPage");
    m_layout->addWidget("RadioButtonsPage", new FluRadioButtonsPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("RelativePanel"), "RelativePanelPage", "LayoutPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("SplitView"), "SplitViewPage", "LayoutPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("StackPanel"), "StackPanelPage", "LayoutPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("VariableSizedWrapGrid"), "VariableSizedWrapGridPage", "LayoutPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("Viewbox"), "ViewboxPage", "LayoutPage");

    connect(layoutPage, &FluLayoutPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);

    makeHNavigationGroup(FluAwesomeType::PreviewLink, tr("Layout"), {
        {tr("Border"), "BorderPage"}, {tr("Canvas"), "CanvasPage"}, {tr("Expander"), "ExpanderPage"},
        {tr("ItemsRepeater"), "ItemsRepeaterPage"}, {tr("Grid"), "GridPage"},
        {tr("RadioButtons"), "RadioButtonsPage"}, {tr("RelativePanel"), "RelativePanelPage"},
        {tr("SplitView"), "SplitViewPage"}, {tr("StackPanel"), "StackPanelPage"},
        {tr("VariableSizedWrapGrid"), "VariableSizedWrapGridPage"}, {tr("Viewbox"), "ViewboxPage"}
    });
}

void FluGalleryWindow::makeMediaNavItem()
{
    m_navView->insertIconTextItem(FluAwesomeType::Calendar, tr("Media"), "MediaPage");
    m_layout->addWidget("MediaPage", new FluMediaPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("AnimatedVisualPlayer"), "AnimatedVisualPlayer", "MediaPage");
    m_navView->insertIconTextItem(FluAwesomeType::None, tr("Capture Element / Camera Preview"), "CaptureElement", "MediaPage");
    m_navView->insertIconTextItem(FluAwesomeType::None, tr("Image"), "Image", "MediaPage");
    m_navView->insertIconTextItem(FluAwesomeType::None, tr("mediaPalyerElement"), "MediaPlayerElement", "MediaPage");
    m_navView->insertIconTextItem(FluAwesomeType::None, tr("PersonPicture"), "PersonPicture", "MediaPage");
    m_navView->insertIconTextItem(FluAwesomeType::None, tr("Sound"), "Sound", "MediaPage");
    m_navView->insertIconTextItem(FluAwesomeType::None, tr("WebView2"), "WebView2", "MediaPage");

    makeHNavigationItem(FluAwesomeType::Calendar, tr("Media"), "MediaPage");
}

void FluGalleryWindow::makeSettingsNavItem()
{
    FluVNavigationSettingsItem *item = new FluVNavigationSettingsItem(FluAwesomeType::Settings, tr("Setting"), this);
    item->setKey("SettingPage");
    m_navView->addItemToBottomLayout(item);

    auto settingsPage = new FluSettingPage;
    m_layout->addWidget("SettingPage", settingsPage);
    connect(item, &FluVNavigationSettingsItem::itemClicked, [=]() { m_layout->setCurrentWidget("SettingPage"); });

    auto hSettingsItem = new FluHNavigationIconTextItem(FluAwesomeType::Settings, tr("Setting"), m_hNavView);
    hSettingsItem->setKey("SettingPage");
    m_hNavView->addItemToLayout(hSettingsItem, FluHNavigationItemPosition::Right);
    connect(hSettingsItem, &FluHNavigationIconTextItem::itemClicked, [=]() {
        m_layout->setCurrentWidget("SettingPage");
    });
}

void FluGalleryWindow::makeMenuToolBarsNavItem()
{
    m_navView->insertIconTextItem(FluAwesomeType::Save, tr("Menus & toolbars"), "MenusAndToolBarsPage");
    auto menusAndToolBarsPage = new FluMenuAndToolBarsPage;
    m_layout->addWidget("MenusAndToolBarsPage", menusAndToolBarsPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("AppBarButton"), "AppBarButtonPage", "MenusAndToolBarsPage");
    m_layout->addWidget("AppBarButtonPage", new FluAppBarButtonPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("AppBarSeparator"), "AppBarSeparator", "MenusAndToolBarsPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("AppBarToggleButton"), "AppBarToggleButtonPage", "MenusAndToolBarsPage");
    m_layout->addWidget("AppBarToggleButtonPage", new FluAppBarToggleButtonPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("CommandBar"), "CommandBarPage", "MenusAndToolBarsPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("MenuBar"), "MenuBarPage", "MenusAndToolBarsPage");
    m_layout->addWidget("MenuBarPage", new FluMenuBarPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("CommandBarFlyout"), "CommandBarFlyoutPage", "MenusAndToolBarsPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("MenuFlyout"), "MenuFlyoutPage", "MenusAndToolBarsPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("SwipeControl"), "SwipeControlPage", "MenusAndToolBarsPage");

    connect(menusAndToolBarsPage, &FluMenuAndToolBarsPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);

    makeHNavigationGroup(FluAwesomeType::BookmarksMirrored, tr("Navigation"), {
        {tr("BreadcrumbBar"), "BreadcrumbBarPage"}, {tr("NavigationView"), "NavigationViewPage"},
        {tr("Pivot"), "PivotPage"}, {tr("TabView"), "TabViewPage"}
    });
}

void FluGalleryWindow::makeNavigationNavItem()
{
    m_navView->insertIconTextItem(FluAwesomeType::BookmarksMirrored, tr("Navigation"), "NavigationPage");
    auto navigationPage = new FluNavigationPage;
    m_layout->addWidget("NavigationPage", navigationPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("BreadcrumbBar"), "BreadcrumbBarPage", "NavigationPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("NavigationView"), "NavigationViewPage", "NavigationPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("Pivot"), "PivotPage", "NavigationPage");
    m_layout->addWidget("PivotPage", new FluPivotPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("TabView"), "TabViewPage", "NavigationPage");

    connect(navigationPage, &FluNavigationPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);

    makeHNavigationGroup(FluAwesomeType::Save, tr("Menus & toolbars"), {
        {tr("AppBarButton"), "AppBarButtonPage"}, {tr("AppBarSeparator"), "AppBarSeparator"},
        {tr("AppBarToggleButton"), "AppBarToggleButton"}, {tr("CommandBar"), "CommandBarPage"},
        {tr("MenuBar"), "MenuBarPage"}, {tr("CommandBarFlyout"), "CommandBarFlyoutPage"},
        {tr("MenuFlyout"), "MenuFlyoutPage"}, {tr("SwipeControl"), "SwipeControlPage"}
    });
}

void FluGalleryWindow::makeScrollingNavItem()
{
    m_navView->insertIconTextItem(FluAwesomeType::Sort, tr("Scrolling"), "ScrollingPage");
    auto scrollingPage = new FluScrollingPage;
    m_layout->addWidget("ScrollingPage", scrollingPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("AnnotatedScrollBar"), "AnnotatedScrollBar", "ScrollingPage");
    m_navView->insertIconTextItem(FluAwesomeType::None, tr("PipsPager"), "PipsPager", "ScrollingPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("ScrollView"), "ScrollViewPage", "ScrollingPage");
    m_layout->addWidget("ScrollViewPage", new FluScrollViewPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("ScrollViewer"), "ScrollViewer", "ScrollingPage");
    m_navView->insertIconTextItem(FluAwesomeType::None, tr("SemanticZoom"), "SemanticZoom", "ScrollingPage");

    connect(scrollingPage, &FluScrollingPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);

    makeHNavigationGroup(FluAwesomeType::Sort, tr("Scrolling"), {
        {tr("AnnotatedScrollBar"), ""}, {tr("PipsPager"), ""},
        {tr("ScrollView"), "ScrollViewPage"}, {tr("ScrollViewer"), ""}, {tr("SemanticZoom"), ""}
    });
}

void FluGalleryWindow::makeStatusInfoNavItem()
{
    m_navView->insertIconTextItem(FluAwesomeType::Reminder, tr("Status & info"), "StatusAndInfoPage");
    auto statusAndInfoPage = new FluStatusAndInfoPage;
    m_layout->addWidget("StatusAndInfoPage", statusAndInfoPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("InfoBadge"), "InfoBadgePage", "StatusAndInfoPage");
    m_layout->addWidget("InfoBadgePage", new FluInfoBadgePage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("InfoBar"), "InfoBarPage", "StatusAndInfoPage");
    m_layout->addWidget("InfoBarPage", new FluInfoBarPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("ProgressBar"), "ProgressBarPage", "StatusAndInfoPage");
    m_layout->addWidget("ProgressBarPage", new FluProgressBarPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("ProgressRing"), "ProgressRingPage", "StatusAndInfoPage");
    m_layout->addWidget("ProgressRingPage", new FluProgressRingPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("ToolTip"), "ToolTip", "StatusAndInfoPage");

    connect(statusAndInfoPage, &FluStatusAndInfoPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);

    makeHNavigationGroup(FluAwesomeType::Reminder, tr("Status & info"), {
        {tr("InfoBadge"), "InfoBadgePage"}, {tr("InfoBar"), "InfoBarPage"},
        {tr("ProgressBar"), "ProgressBarPage"}, {tr("ProgressRing"), "ProgressRingPage"},
        {tr("ToolTip"), "ProgressRingPage"}
    });
}

void FluGalleryWindow::makeTextNavItem()
{
    m_navView->insertIconTextItem(FluAwesomeType::Font, tr("Text"), "TextPage");
    auto textPage = new FluTextPage;
    m_layout->addWidget("TextPage", textPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("AutoSuggestBox"), "AutoSuggestBoxPage", "TextPage");
    m_layout->addWidget("AutoSuggestBoxPage", new FluAutoSuggestBoxPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("NumberBox"), "NumberBoxPage", "TextPage");
    m_layout->addWidget("NumberBoxPage", new FluNumberBoxPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("PasswordBox"), "PasswordBoxPage", "TextPage");
    m_layout->addWidget("PasswordBoxPage", new FluPasswordBoxPage);

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("RichEditBox"), "RichEditBoxPage", "TextPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("RichTextBlock"), "RichTextBlockPage", "TextPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("TextBlock"), "TextBlockPage", "TextPage");

    m_navView->insertIconTextItem(FluAwesomeType::None, tr("TextBox"), "TextBoxPage", "TextPage");
    m_layout->addWidget("TextBoxPage", new FluTextBoxPage);

    connect(textPage, &FluTextPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);

    makeHNavigationGroup(FluAwesomeType::Font, tr("Text"), {
        {tr("AutoSuggestBox"), "AutoSuggestBoxPage"}, {tr("NumberBox"), "NumberBoxPage"},
        {tr("PasswordBox"), "PasswordBoxPage"}, {tr("RichEditBox"), "RichEditBoxPage"},
        {tr("RichTextBlock"), "RichTextBlockPage"}, {tr("TextBlock"), "TextBlockPage"},
        {tr("TextBox"), "TextBoxPage"}
    });
}

void FluGalleryWindow::resizeEvent(QResizeEvent *event)
{
}

void FluGalleryWindow::closeEvent(QCloseEvent *event)
{
    FluMessageBox messageBox(tr("Close Gallery Window?"), tr("choose \"Ok\" to close. choose \"Cancel\" do nothing."), this);
    int exec = messageBox.exec();
    if (exec == QDialog::Rejected)
    {
        event->ignore();
        return;
    }
    else if (exec == QDialog::Accepted)
    {
        // 保存导航栏状态
        FluConfigUtils::getUtils()->setNavWidth(m_navView->getViewWidth());
        FluConfigUtils::getUtils()->setNavStyle(m_isHorizontalNav ? 1 : 0);
        FluConfigUtils::getUtils()->setViewCollapsed(!m_navView->isLong());
        QApplication::quit();
    }
}

void FluGalleryWindow::onClickedHCard(QString key)
{
    auto item = m_navView->getItemByKey(key);
    if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
    {
        auto iconTextItem = (FluVNavigationIconTextItem *)(item);
        iconTextItem->onItemClickedDirect();
        m_layout->setCurrentWidget(key);
    }
}

void FluGalleryWindow::onThemeChanged()
{
#if !defined USE_WINDOWKIT_WIDGET
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
        // FluStyleSheetUtils::setQssByFileName("../stylesheet/light/FluGalleryWindow.qss", this);
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
        // FluStyleSheetUtils::setQssByFileName("../stylesheet/dark/FluGalleryWindow.qss", this);
    }
#endif
    FluStyleSheetUtils::setQssByFileName("FluGalleryWindow.qss", this, FluThemeUtils::getUtils()->getTheme());
}
