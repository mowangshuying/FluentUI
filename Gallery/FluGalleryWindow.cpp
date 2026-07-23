#include "FluGalleryWindow.h"
#include "FluAEmptyPage.h"
#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>
#include "../Controls/FluMessageBox.h"
#include <QApplication>
#include <QTimer>
#include "../Controls/FluThemeButton.h"
#include "FluEmoijsPage.h"

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

    // QString qss = FluStyleSheetUtils::getQssByFileName("../StyleSheet/light/FluGalleryWindow.qss");
    // setStyleSheet(qss);

    m_navView = new FluVNavigationView(this);
    m_layout = new FluStackedLayout;

    m_contentLayout->addWidget(m_navView);
    m_contentLayout->addLayout(m_layout, 1);

    m_hNavView = new FluHNavigationView(this);
    m_hNavView->setObjectName("horizontalNavView");
    m_mainLayout->insertWidget(1, m_hNavView);
    m_hNavView->hide();
    m_isHorizontalNav = false;

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
    m_navView->setViewWidth(300);
    m_navView->setOnlyCollapseView(false);
    onThemeChanged();
}

void FluGalleryWindow::makeHNavigationGroup(FluAwesomeType type, QString text, std::vector<QPair<QString, QString>> items)
{
    auto parent = new FluHNavigationIconTextItem(type, text, m_hNavView);
    m_hNavView->addItemToMidLayout(parent);
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
    m_hNavView->addItemToMidLayout(item);
    connect(item, &FluHNavigationIconTextItem::itemClicked, this, [=]() {
        m_layout->setCurrentWidget(key);
    });
}

void FluGalleryWindow::animateNavSwitch(bool toHorizontal)
{
    setProperty("horizontalNav", toHorizontal);
    style()->polish(this);

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
        vAnim->setEndValue(300);
        connect(vAnim, &QPropertyAnimation::finished, this, [=]() {
            m_navView->setMaximumWidth(QWIDGETSIZE_MAX);
            m_navView->setFixedWidth(300);
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
}

void FluGalleryWindow::makeHomeNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Home, tr("Home"), this);
    item->setKey("HomePage");
    m_navView->addItemToMidLayout(item);

    auto homePage = new FluHomePage;
    m_layout->addWidget("HomePage", homePage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("HomePage"); });

    connect(homePage, &FluHomePage::clickedHCard, [=](QString key) {
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_layout->setCurrentWidget(key);
        }
    });

    makeHNavigationItem(FluAwesomeType::Home, tr("Home"), "HomePage");
}

void FluGalleryWindow::makeDesignGuidanceNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Design, tr("Design guidance"), this);
    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem(FluAwesomeType::FontSize, tr("Typography"), item);
    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem(FluAwesomeType::EmojiTabSymbols, tr("Icons"), item);
    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem(FluAwesomeType::Emoji, tr("Emoijs"), item);

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem(FluAwesomeType::Airplane, tr("2-level"), item);

    FluVNavigationIconTextItem *item41 = new FluVNavigationIconTextItem(FluAwesomeType::Airplane, tr("3-level"), item4);
    FluVNavigationIconTextItem *item42 = new FluVNavigationIconTextItem(FluAwesomeType::Airplane, tr("3-level"), item4);
    FluVNavigationIconTextItem *item43 = new FluVNavigationIconTextItem(FluAwesomeType::Airplane, tr("3-level"), item4);

    FluVNavigationIconTextItem *item421 = new FluVNavigationIconTextItem(FluAwesomeType::Airplane, tr("4-level"), item42);
    FluVNavigationIconTextItem *item422 = new FluVNavigationIconTextItem(FluAwesomeType::Airplane, tr("4-level"), item42);
    FluVNavigationIconTextItem *item423 = new FluVNavigationIconTextItem(FluAwesomeType::Airplane, tr("4-level"), item42);

    FluVNavigationIconTextItem *item5231 = new FluVNavigationIconTextItem(FluAwesomeType::Airplane, tr("5-level"), item42);
    FluVNavigationIconTextItem *item5232 = new FluVNavigationIconTextItem(FluAwesomeType::Airplane, tr("5-level"), item42);
    FluVNavigationIconTextItem *item5233 = new FluVNavigationIconTextItem(FluAwesomeType::Airplane, tr("5-level"), item42);
    FluVNavigationIconTextItem *item5234 = new FluVNavigationIconTextItem(FluAwesomeType::Airplane, tr("5-level"), item42);

    item1->setKey("TypographyPage");

    item->addItem(item1);

    item2->setKey("IconsPage");

    // LOG_DEBUG << "item2 depth Before:" << item2->getDepth();
    item->addItem(item2);
    // LOG_DEBUG << "item2 depth After:" << item2->getDepth();

    item3->setKey("EmoijsPage");
    item->addItem(item3);

    item4->addItem(item41);
    item4->addItem(item42);
    item4->addItem(item43);

    // LOG_DEBUG << "item41 depth:" << item41->getDepth();
    // LOG_DEBUG << "item42 depth:" << item42->getDepth();
    // LOG_DEBUG << "item43 depth:" << item43->getDepth();

    item41->addItem(item421);
    item41->addItem(item422);
    item41->addItem(item423);

    item423->addItem(item5231);
    item423->addItem(item5232);
    item423->addItem(item5233);
    item423->addItem(item5234);

    // LOG_DEBUG << "item421 depth:" << item421->getDepth();
    // LOG_DEBUG << "item422 depth:" << item422->getDepth();
    // LOG_DEBUG << "item423 depth:" << item423->getDepth();

    item->addItem(item4);

    // item->addItem(item3);
    m_navView->addItemToMidLayout(item);

    auto typographyPage = new FluTypeographyPage;
    m_layout->addWidget("TypographyPage", typographyPage);

    connect(item1, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("TypographyPage"); });

    auto iconsPage = new FluIconsPage;
    m_layout->addWidget("IconsPage", iconsPage);
    connect(item2, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("IconsPage"); });

    auto emoijsPage = new FluEmoijsPage;
    m_layout->addWidget("EmoijsPage", emoijsPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("EmoijsPage"); });
}

void FluGalleryWindow::makeSamplesNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::AllApps, tr("All samples"), this);
    item->setKey("AllSamplesPage");
    m_navView->addItemToMidLayout(item);

    auto allSamplesPage = new FluAllSamplesPage;
    m_layout->addWidget("AllSamplesPage", allSamplesPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("AllSamplesPage"); });

    connect(allSamplesPage, &FluAllSamplesPage::clickedHCard, [=](QString key) {
        // LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_layout->setCurrentWidget(key);
        }
    });

    makeHNavigationItem(FluAwesomeType::AllApps, tr("All samples"), "AllSamplesPage");
}

void FluGalleryWindow::makeBasicInputNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::CheckboxComposite, tr("Basic input"), this);
    item->setKey("BasicInputPage");

    auto basicInputPage = new FluBasicInputPage;
    m_layout->addWidget("BasicInputPage", basicInputPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("BasicInputPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem(tr("InputValidation"), item);
    item1->enableThisItem(false);

    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem(tr("Button"), item);
    auto buttonPage = new FluButtonPage;
    item2->setKey("ButtonPage");
    m_layout->addWidget("ButtonPage", buttonPage);
    connect(item2, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("ButtonPage"); });

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem(tr("DropDownButton"), item);
    item3->setKey("DropDownButtonPage");
    auto dropDownPage = new FluDropDownButtonPage;
    m_layout->addWidget("DropDownButtonPage", dropDownPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("DropDownButtonPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem(tr("HyperLinkButton"), item);
    item4->setKey("HyperLinkButtonPage");
    auto hyperLinkButtonPage = new FluHyperLinkButtonPage;
    m_layout->addWidget("HyperLinkButtonPage", hyperLinkButtonPage);
    connect(item4, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("HyperLinkButtonPage"); });

    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem(tr("RepeatButton"), item);
    item5->setKey("RepeatButtonPage");
    auto repeatButtonPage = new FluRepeatButtonPage;
    m_layout->addWidget("RepeatButtonPage", repeatButtonPage);
    connect(item5, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("RepeatButtonPage"); });

    FluVNavigationIconTextItem *item6 = new FluVNavigationIconTextItem(tr("ToggleButton"), item);
    item6->setKey("ToggleButtonPage");
    auto toggleButtonPage = new FluToggleButtonPage;
    m_layout->addWidget("ToggleButtonPage", toggleButtonPage);
    connect(item6, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("ToggleButtonPage"); });

    FluVNavigationIconTextItem *item7 = new FluVNavigationIconTextItem(tr("SplitButton"), item);
    item7->setKey("SplitButtonPage");
    auto splitButtonPage = new FluSplitButtonPage;
    m_layout->addWidget("SplitButtonPage", splitButtonPage);
    connect(item7, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("SplitButtonPage"); });

    FluVNavigationIconTextItem *item8 = new FluVNavigationIconTextItem(tr("ToggleSplitButton"), item);

    FluVNavigationIconTextItem *item9 = new FluVNavigationIconTextItem(tr("CheckBox"), item);
    item9->setKey("CheckBoxPage");
    auto checkBoxPage = new FluCheckBoxPage;
    m_layout->addWidget("CheckBoxPage", checkBoxPage);
    connect(item9, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("CheckBoxPage"); });

    FluVNavigationIconTextItem *item10 = new FluVNavigationIconTextItem(tr("ColorPicker"), item);
    item10->setKey("ColorPickerPage");
    auto colorPickerPage = new FluColorPickerPage;
    m_layout->addWidget("ColorPickerPage", colorPickerPage);
    connect(item10, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("ColorPickerPage"); });

    FluVNavigationIconTextItem *item11 = new FluVNavigationIconTextItem(tr("ComboBox"), item);
    item11->setKey("ComboBoxPage");
    auto comboBoxPage = new FluComboBoxPage;
    m_layout->addWidget("ComboBoxPage", comboBoxPage);
    connect(item11, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("ComboBoxPage"); });

    FluVNavigationIconTextItem *item12 = new FluVNavigationIconTextItem(tr("RadioButton"), item);
    item12->setKey("RadioButtonPage");
    auto radioButtonPage = new FluRadioButtonPage;
    m_layout->addWidget("RadioButtonPage", radioButtonPage);
    connect(item12, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("RadioButtonPage"); });

    FluVNavigationIconTextItem *item13 = new FluVNavigationIconTextItem(tr("RatingControl"), item);
    item13->setKey("RatingControlPage");
    auto ratingControlPage = new FluRatingControlPage;
    m_layout->addWidget("RatingControlPage", ratingControlPage);
    connect(item13, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("RatingControlPage"); });

    FluVNavigationIconTextItem *item14 = new FluVNavigationIconTextItem(tr("Slider"), item);
    item14->setKey("SliderPage");
    auto sliderPage = new FluSliderPage;
    m_layout->addWidget("SliderPage", sliderPage);
    connect(item14, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("SliderPage"); });

    FluVNavigationIconTextItem *item15 = new FluVNavigationIconTextItem(tr("ToggleSwitch"), item);
    item15->setKey("ToggleSwitchPage");
    auto toggleSwitchPage = new FluToggleSwitchPage;
    m_layout->addWidget("ToggleSwitchPage", toggleSwitchPage);
    connect(item15, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("ToggleSwitchPage"); });

    connect(basicInputPage, &FluBasicInputPage::clickedHCard, [=](QString key) {
        // LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_layout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    item->addItem(item5);
    item->addItem(item6);
    item->addItem(item7);
    item->addItem(item8);
    item->addItem(item9);
    item->addItem(item10);
    item->addItem(item11);
    item->addItem(item12);
    item->addItem(item13);
    item->addItem(item14);
    item->addItem(item15);
    m_navView->addItemToMidLayout(item);

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
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::TiltDown, tr("Connections"), this);
    item->setKey("ConnectionsPage");
    auto collectionsPage = new FluCollectionsPage;
    m_layout->addWidget("CollectionsPage", collectionsPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("CollectionsPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem(tr("FlipView"), item);
    item1->setKey("FlipViewPage");

    auto flipViewPage = new FluFlipViewPage;
    m_layout->addWidget("FlipViewPage", flipViewPage);
    connect(item1, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("FlipViewPage"); });

    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem(tr("ListView"), item);
    item5->setKey("ListViewPage");

    auto listViewPage = new FluListViewPage;
    m_layout->addWidget("ListViewPage", listViewPage);
    connect(item5, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("ListViewPage"); });

    FluVNavigationIconTextItem *item7 = new FluVNavigationIconTextItem(tr("TreeView"), item);
    item7->setKey("TreeViewPage");
    auto treeViewPage = new FluTreeViewPage;
    m_layout->addWidget("TreeViewPage", treeViewPage);
    connect(item7, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("TreeViewPage"); });

    FluVNavigationIconTextItem *item8 = new FluVNavigationIconTextItem(tr("TableView"), item);
    item8->setKey("TableViewPage");
    auto tableViewPage = new FluTableViewPage;
    m_layout->addWidget("TableViewPage", tableViewPage);
    connect(item8, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("TableViewPage"); });

    connect(collectionsPage, &FluCollectionsPage::clickedHCard, [=](QString key) {
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_layout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item5);
    item->addItem(item7);
    item->addItem(item8);
    m_navView->addItemToMidLayout(item);

    makeHNavigationGroup(FluAwesomeType::TiltDown, tr("Connections"), {
        {tr("FlipView"), "FlipViewPage"}, {tr("ListView"), "ListViewPage"},
        {tr("TreeView"), "TreeViewPage"}, {tr("TableView"), "TableViewPage"}
    });
}

void FluGalleryWindow::makDateTimeNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Calendar, tr("Date & time"), this);
    item->setKey("DateAndTimePage");
    auto dateAndTimePage = new FluDateAndTimePage;
    m_layout->addWidget("DateAndTimePage", dateAndTimePage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("DateAndTimePage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem(tr("CalendarDatePicker"), item);
    item1->setKey("CalendarDatePickerPage");
    auto calendarDatePickerPage = new FluCalendarDatePickerPage;
    m_layout->addWidget("CalendarDatePickerPage", calendarDatePickerPage);
    connect(item1, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("CalendarDatePickerPage"); });

    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem(tr("CalendarView"), item);
    item2->setKey("CalendarViewPage");
    auto calendarViewPage = new FluCalendarViewPage;
    m_layout->addWidget("CalendarViewPage", calendarViewPage);
    connect(item2, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("CalendarViewPage"); });

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem(tr("DatePicker"), item);
    item3->setKey("DatePickerPage");
    auto datePickerPage = new FluDatePickerPage;
    m_layout->addWidget("DatePickerPage", datePickerPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("DatePickerPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem(tr("TimePicker"), item);
    item4->setKey("TimePickerPage");
    auto timePickerPage = new FluTimePickerPage;
    m_layout->addWidget("TimePickerPage", timePickerPage);
    connect(item4, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("TimePickerPage"); });

    connect(dateAndTimePage, &FluDateAndTimePage::clickedHCard, [=](QString key) {
        // LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_layout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);

    m_navView->addItemToMidLayout(item);

    makeHNavigationGroup(FluAwesomeType::Calendar, tr("Date & time"), {
        {tr("CalendarDatePicker"), "CalendarDatePickerPage"}, {tr("CalendarView"), "CalendarViewPage"},
        {tr("DatePicker"), "DatePickerPage"}, {tr("TimePicker"), "TimePickerPage"}
    });
}

void FluGalleryWindow::makeDialogsFlyouts()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Comment, tr("Dialogs & flyouts"), this);
    item->setKey("DialogsAndFlyoutsPage");
    auto dialogAndFlyoutPage = new FluDialogsAndFlyoutsPage;
    m_layout->addWidget("DialogsAndFlyoutsPage", dialogAndFlyoutPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("DialogsAndFlyoutsPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem(tr("ContentDialog"), item);
    item1->setKey("ContentDialogPage");

    auto contentDialogPage = new FluContentDialogPage;
    m_layout->addWidget("ContentDialogPage", contentDialogPage);
    connect(item1, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("ContentDialogPage"); });

    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem(tr("Flyout"), item);
    item2->setKey("FlyoutPage");

    auto flyoutPage = new FluFlyoutPage;
    m_layout->addWidget("FlyoutPage", flyoutPage);
    connect(item2, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("FlyoutPage"); });

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem(tr("TeachingTip"), item);
    item3->setKey("TeachingTipPage");

    connect(dialogAndFlyoutPage, &FluDialogsAndFlyoutsPage::clickedHCard, [=](QString key) {
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_layout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    m_navView->addItemToMidLayout(item);

    makeHNavigationGroup(FluAwesomeType::Comment, tr("Dialogs & flyouts"), {
        {tr("ContentDialog"), "ContentDialogPage"}, {tr("Flyout"), "FlyoutPage"},
        {tr("TeachingTip"), "TeachingTipPage"}
    });
}

void FluGalleryWindow::makeLayoutNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::PreviewLink, tr("Layout"), this);
    item->setKey("LayoutPage");
    auto layoutPage = new FluLayoutPage;
    m_layout->addWidget("LayoutPage", layoutPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("LayoutPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem(tr("Border"), item);
    item1->setKey("BorderPage");
    auto borderPage = new FluBorderPage;
    m_layout->addWidget("BorderPage", borderPage);
    connect(item1, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("BorderPage"); });

    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem(tr("Canvas"), item);
    item2->setKey("CanvasPage");

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem(tr("Expander"), item);
    item3->setKey("ExpanderPage");
    auto expanderPage = new FluExpanderPage;
    m_layout->addWidget("ExpanderPage", expanderPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("ExpanderPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem(tr("ItemsRepeater"), item);
    item4->setKey("ItemsRepeaterPage");

    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem(tr("Grid"), item);
    item5->setKey("GridPage");

    FluVNavigationIconTextItem *item6 = new FluVNavigationIconTextItem(tr("RadioButtons"), item);
    item6->setKey("RadioButtonsPage");
    auto radioButtonsPage = new FluRadioButtonsPage;
    m_layout->addWidget("RadioButtonsPage", radioButtonsPage);
    connect(item6, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("RadioButtonsPage"); });

    FluVNavigationIconTextItem *item7 = new FluVNavigationIconTextItem(tr("RelativePanel"), item);
    item7->setKey("RelativePanelPage");

    FluVNavigationIconTextItem *item8 = new FluVNavigationIconTextItem(tr("SplitView"), item);
    item8->setKey("SplitViewPage");

    FluVNavigationIconTextItem *item9 = new FluVNavigationIconTextItem(tr("StackPanel"), item);
    item9->setKey("StackPanelPage");

    FluVNavigationIconTextItem *item10 = new FluVNavigationIconTextItem(tr("VariableSizedWrapGrid"), item);
    item10->setKey("VariableSizedWrapGridPage");

    FluVNavigationIconTextItem *item11 = new FluVNavigationIconTextItem(tr("Viewbox"), item);
    item11->setKey("ViewboxPage");

    connect(layoutPage, &FluLayoutPage::clickedHCard, [=](QString key) {
        // LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_layout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    item->addItem(item5);
    item->addItem(item6);
    item->addItem(item7);
    item->addItem(item8);
    item->addItem(item9);
    item->addItem(item10);
    item->addItem(item11);
    m_navView->addItemToMidLayout(item);

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
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Calendar, tr("Media"), this);
    item->setKey("MediaPage");
    auto mediaPage = new FluMediaPage;
    m_layout->addWidget("MediaPage", mediaPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("MediaPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem(tr("AnimatedVisualPlayer"), item);
    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem(tr("Capture Element / Camera Preview"), item);
    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem(tr("Image"), item);
    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem(tr("mediaPalyerElement"), item);
    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem(tr("PersonPicture"), item);
    FluVNavigationIconTextItem *item6 = new FluVNavigationIconTextItem(tr("Sound"), item);
    FluVNavigationIconTextItem *item7 = new FluVNavigationIconTextItem(tr("WebView2"), item);

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    item->addItem(item5);
    item->addItem(item6);
    item->addItem(item7);
    m_navView->addItemToMidLayout(item);

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
    m_hNavView->addItemToRightLayout(hSettingsItem);
    connect(hSettingsItem, &FluHNavigationIconTextItem::itemClicked, [=]() {
        m_layout->setCurrentWidget("SettingPage");
    });
}

void FluGalleryWindow::makeMenuToolBarsNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Save, tr("Menus & toolbars"), this);
    item->setKey("MenusAndToolBarsPage");
    auto menusAndToolBarsPage = new FluMenuAndToolBarsPage;
    m_layout->addWidget("MenusAndToolBarsPage", menusAndToolBarsPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("MenusAndToolBarsPage"); });

    //  FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem("XamlUICommand", item);
    //  FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem("StandardUICommand", item);
    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem(tr("AppBarButton"), item);
    item3->setKey("AppBarButtonPage");
    auto appBarButtonPage = new FluAppBarButtonPage;
    m_layout->addWidget("AppBarButtonPage", appBarButtonPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("AppBarButtonPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem(tr("AppBarSeparator"), item);
    item4->setKey("AppBarSeparator");

    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem(tr("AppBarToggleButton"), item);
    item5->setKey("AppBarToggleButton");
    auto appBarToggleButtonPage = new FluAppBarToggleButtonPage;
    m_layout->addWidget("AppBarToggleButtonPage", appBarToggleButtonPage);
    connect(item5, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("AppBarToggleButtonPage"); });

    FluVNavigationIconTextItem *item6 = new FluVNavigationIconTextItem(tr("CommandBar"), item);
    item6->setKey("CommandBarPage");

    FluVNavigationIconTextItem *item7 = new FluVNavigationIconTextItem(tr("MenuBar"), item);
    item7->setKey("MenuBarPage");
    auto menuBarPage = new FluMenuBarPage;
    m_layout->addWidget("MenuBarPage", menuBarPage);
    connect(item7, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("MenuBarPage"); });

    FluVNavigationIconTextItem *item8 = new FluVNavigationIconTextItem(tr("CommandBarFlyout"), item);
    item8->setKey("CommandBarFlyoutPage");

    FluVNavigationIconTextItem *item9 = new FluVNavigationIconTextItem(tr("MenuFlyout"), item);
    item9->setKey("MenuFlyoutPage");

    FluVNavigationIconTextItem *item10 = new FluVNavigationIconTextItem(tr("SwipeControl"), item);
    item10->setKey("SwipeControlPage");

    connect(menusAndToolBarsPage, &FluMenuAndToolBarsPage::clickedHCard, [=](QString key) {
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_layout->setCurrentWidget(key);
        }
    });

    item->addItem(item3);
    item->addItem(item4);
    item->addItem(item5);
    item->addItem(item6);
    item->addItem(item7);
    item->addItem(item8);
    item->addItem(item9);
    item->addItem(item10);
    m_navView->addItemToMidLayout(item);

    makeHNavigationGroup(FluAwesomeType::BookmarksMirrored, tr("Navigation"), {
        {tr("BreadcrumbBar"), "BreadcrumbBarPage"}, {tr("NavigationView"), "NavigationViewPage"},
        {tr("Pivot"), "PivotPage"}, {tr("TabView"), "TabViewPage"}
    });
}

void FluGalleryWindow::makeNavigationNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::BookmarksMirrored, tr("Navigation"), this);
    item->setKey("NavigationPage");
    auto navigationPage = new FluNavigationPage;
    m_layout->addWidget("NavigationPage", navigationPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("NavigationPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem(tr("BreadcrumbBar"), item);
    item1->setKey("BreadcrumbBarPage");

    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem(tr("NavigationView"), item);
    item2->setKey("NavigationViewPage");

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem(tr("Pivot"), item);
    item3->setKey("PivotPage");
    auto pivotPage = new FluPivotPage;
    m_layout->addWidget("PivotPage", pivotPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("PivotPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem(tr("TabView"), item);
    item4->setKey("TabViewPage");

    connect(navigationPage, &FluNavigationPage::clickedHCard, [=](QString key) {
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_layout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    m_navView->addItemToMidLayout(item);

    makeHNavigationGroup(FluAwesomeType::Save, tr("Menus & toolbars"), {
        {tr("AppBarButton"), "AppBarButtonPage"}, {tr("AppBarSeparator"), "AppBarSeparator"},
        {tr("AppBarToggleButton"), "AppBarToggleButton"}, {tr("CommandBar"), "CommandBarPage"},
        {tr("MenuBar"), "MenuBarPage"}, {tr("CommandBarFlyout"), "CommandBarFlyoutPage"},
        {tr("MenuFlyout"), "MenuFlyoutPage"}, {tr("SwipeControl"), "SwipeControlPage"}
    });
}

void FluGalleryWindow::makeScrollingNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Sort, tr("Scrolling"), this);
    item->setKey("ScrollingPage");
    auto scrollingPage = new FluScrollingPage;
    m_layout->addWidget("ScrollingPage", scrollingPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("ScrollingPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem(tr("AnnotatedScrollBar"), item);
    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem(tr("PipsPager"), item);

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem(tr("ScrollView"), item);
    item3->setKey("ScrollViewPage");
    auto scrollViewPage = new FluScrollViewPage;
    m_layout->addWidget("ScrollViewPage", scrollViewPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("ScrollViewPage"); });

    connect(scrollingPage, &FluScrollingPage::clickedHCard, [=](QString key) {
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_layout->setCurrentWidget(key);
        }
    });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem(tr("ScrollViewer"), item);
    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem(tr("SemanticZoom"), item);

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    item->addItem(item5);
    m_navView->addItemToMidLayout(item);

    makeHNavigationGroup(FluAwesomeType::Sort, tr("Scrolling"), {
        {tr("AnnotatedScrollBar"), ""}, {tr("PipsPager"), ""},
        {tr("ScrollView"), "ScrollViewPage"}, {tr("ScrollViewer"), ""}, {tr("SemanticZoom"), ""}
    });
}

void FluGalleryWindow::makeStatusInfoNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Reminder, tr("Status & info"), this);
    item->setKey("StatusAndInfoPage");
    auto statusAndInfoPage = new FluStatusAndInfoPage;
    m_layout->addWidget("StatusAndInfoPage", statusAndInfoPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("StatusAndInfoPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem(tr("InfoBadge"), item);
    item1->setKey("InfoBadgePage");
    auto infoBadgePage = new FluInfoBadgePage;
    m_layout->addWidget("InfoBadgePage", infoBadgePage);
    connect(item1, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("InfoBadgePage"); });

    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem(tr("InfoBar"), item);
    item2->setKey("InfoBarPage");

    auto infoBarPage = new FluInfoBarPage;
    m_layout->addWidget("InfoBarPage", infoBarPage);
    connect(item2, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("InfoBarPage"); });

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem(tr("ProgressBar"), item);
    item3->setKey("ProgressBarPage");
    auto progressBarPage = new FluProgressBarPage;
    m_layout->addWidget("ProgressBarPage", progressBarPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("ProgressBarPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem(tr("ProgressRing"), item);
    item4->setKey("ProgressRingPage");

    auto progressRingPage = new FluProgressRingPage;
    m_layout->addWidget("ProgressRingPage", progressRingPage);
    connect(item4, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("ProgressRingPage"); });

    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem(tr("ToolTip"), item);
    item5->setKey("ProgressRingPage");

    connect(statusAndInfoPage, &FluStatusAndInfoPage::clickedHCard, [=](QString key) {
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_layout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    item->addItem(item5);
    m_navView->addItemToMidLayout(item);

    makeHNavigationGroup(FluAwesomeType::Reminder, tr("Status & info"), {
        {tr("InfoBadge"), "InfoBadgePage"}, {tr("InfoBar"), "InfoBarPage"},
        {tr("ProgressBar"), "ProgressBarPage"}, {tr("ProgressRing"), "ProgressRingPage"},
        {tr("ToolTip"), "ProgressRingPage"}
    });
}

void FluGalleryWindow::makeTextNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Font, tr("Text"), this);
    item->setKey("TextPage");
    auto textPage = new FluTextPage;
    m_layout->addWidget("TextPage", textPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("TextPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem(tr("AutoSuggestBox"), item);
    item1->setKey("AutoSuggestBoxPage");
    auto autoSuggestBoxPage = new FluAutoSuggestBoxPage;
    m_layout->addWidget("AutoSuggestBoxPage", autoSuggestBoxPage);
    connect(item1, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("AutoSuggestBoxPage"); });

    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem(tr("NumberBox"), item);
    item2->setKey("NumberBoxPage");
    auto numberBoxPage = new FluNumberBoxPage;
    m_layout->addWidget("NumberBoxPage", numberBoxPage);
    connect(item2, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("NumberBoxPage"); });

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem(tr("PasswordBox"), item);
    item3->setKey("PasswordBoxPage");
    auto passwordBoxPage = new FluPasswordBoxPage;
    m_layout->addWidget("PasswordBoxPage", passwordBoxPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("PasswordBoxPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem(tr("RichEditBox"), item);
    item4->setKey("RichEditBoxPage");

    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem(tr("RichTextBlock"), item);
    item5->setKey("RichTextBlockPage");

    FluVNavigationIconTextItem *item6 = new FluVNavigationIconTextItem(tr("TextBlock"), item);
    item6->setKey("TextBlockPage");

    FluVNavigationIconTextItem *item7 = new FluVNavigationIconTextItem(tr("TextBox"), item);
    item7->setKey("TextBoxPage");
    auto textBoxPage = new FluTextBoxPage;
    m_layout->addWidget("TextBoxPage", textBoxPage);
    connect(item7, &FluVNavigationIconTextItem::itemClicked, [=]() { m_layout->setCurrentWidget("TextBoxPage"); });

    connect(textPage, &FluTextPage::clickedHCard, [=](QString key) {
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_layout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    item->addItem(item5);
    item->addItem(item6);
    item->addItem(item7);
    m_navView->addItemToMidLayout(item);

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
        // event->accept();
        QApplication::quit();
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
        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/light/FluGalleryWindow.qss", this);
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
        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/dark/FluGalleryWindow.qss", this);
    }
#endif
    FluStyleSheetUtils::setQssByFileName("FluGalleryWindow.qss", this, FluThemeUtils::getUtils()->getTheme());
}
