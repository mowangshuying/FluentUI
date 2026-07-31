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

    m_vNavView = new FluVNavigationView(this);
    m_layout = new FluStackedLayout;

    m_contentLayout->addWidget(m_vNavView);
    m_contentLayout->addLayout(m_layout, 1);

    m_hNavView = new FluHNavigationView(this);
    m_hNavView->setObjectName("horizontalNavView");
    m_mainLayout->insertWidget(1, m_hNavView);
    
    if (m_isHorizontalNav) {
        m_vNavView->hide();
        m_hNavView->show();
    } else {
        m_vNavView->show();
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

    m_vNavView->updateSearchKeys();

    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    connect(m_vNavView, &FluVNavigationView::searchKeyChanged, this, [=](QString text) { m_layout->setCurrentWidget(text); });
    connect(m_vNavView, &FluVNavigationView::keyChanged, this, [=](QString key) { m_layout->setCurrentWidget(key); });
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
    m_vNavView->setViewWidth(navWidth > 0 ? navWidth : 300);
    m_vNavView->setOnlyCollapseView(false);

    if (!m_isHorizontalNav && FluConfigUtils::getUtils()->getViewCollapsed())
        m_vNavView->collapseView();

    onThemeChanged();
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
        m_vNavView->setFixedWidth(m_vNavView->width());
        auto vAnim = new QPropertyAnimation(m_vNavView, "maximumWidth", this);
        vAnim->setDuration(200);
        vAnim->setEasingCurve(QEasingCurve::OutCubic);
        vAnim->setStartValue(m_vNavView->width());
        vAnim->setEndValue(0);
        connect(vAnim, &QPropertyAnimation::finished, this, [=]() {
            m_vNavView->setVisible(false);
            m_vNavView->setMaximumWidth(QWIDGETSIZE_MAX);
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
        m_vNavView->setFixedWidth(0);
        m_vNavView->setVisible(true);
        auto vAnim = new QPropertyAnimation(m_vNavView, "maximumWidth", this);
        vAnim->setDuration(200);
        vAnim->setEasingCurve(QEasingCurve::OutCubic);
        vAnim->setStartValue(0);

        ///
        vAnim->setEndValue(m_vNavView->calcViewWidthByIsLong());
        connect(vAnim, &QPropertyAnimation::finished, this, [=]() {
            m_vNavView->setMaximumWidth(QWIDGETSIZE_MAX);
            m_vNavView->setFixedWidth(m_vNavView->calcViewWidthByIsLong());
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
    makeHomeHNavItem();
    makeHomeVNavItem();

    auto homePage = new FluHomePage;
    m_layout->addWidget("HomePage", homePage);

    connect(homePage, &FluHomePage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);
}

void FluGalleryWindow::makeHomeHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::Home, tr("Home"), "HomePage");
}

void FluGalleryWindow::makeHomeVNavItem()
{
    m_vNavView->insertIconTextItem(FluAwesomeType::Home, tr("Home"), "HomePage");
}

void FluGalleryWindow::makeDesignGuidanceNavItem()
{
    makeDesignGuidanceHNavItem();
    makeDesignGuidanceVNavItem();

    auto typographyPage = new FluTypeographyPage;
    m_layout->addWidget("TypographyPage", typographyPage);
    auto iconsPage = new FluIconsPage;
    m_layout->addWidget("IconsPage", iconsPage);
    auto emoijsPage = new FluEmoijsPage;
    m_layout->addWidget("EmoijsPage", emoijsPage);
}

void FluGalleryWindow::makeDesignGuidanceHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::Design, tr("Design guidance"), "DesignGuidancePage");
    m_hNavView->insertIconTextItem(FluAwesomeType::FontSize, tr("Typography"), "TypographyPage", "DesignGuidancePage");
    m_hNavView->insertIconTextItem(FluAwesomeType::EmojiTabSymbols, tr("Icons"), "IconsPage", "DesignGuidancePage");
    m_hNavView->insertIconTextItem(FluAwesomeType::Emoji, tr("Emoijs"), "EmoijsPage", "DesignGuidancePage");
}

void FluGalleryWindow::makeDesignGuidanceVNavItem()
{
    m_vNavView->insertIconTextItem(FluAwesomeType::Design, tr("Design guidance"), "DesignGuidancePage");
    m_vNavView->insertIconTextItem(FluAwesomeType::FontSize, tr("Typography"), "TypographyPage", "DesignGuidancePage");
    m_vNavView->insertIconTextItem(FluAwesomeType::EmojiTabSymbols, tr("Icons"), "IconsPage", "DesignGuidancePage");
    m_vNavView->insertIconTextItem(FluAwesomeType::Emoji, tr("Emoijs"), "EmoijsPage", "DesignGuidancePage");
    m_vNavView->insertIconTextItem(FluAwesomeType::Airplane, tr("2.level"), "2.levelPage", "DesignGuidancePage");
    m_vNavView->insertIconTextItem(FluAwesomeType::Airplane, tr("3.level1"), "3.level1Page", "2.levelPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::Airplane, tr("3.level2"), "3.level2Page", "2.levelPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::Airplane, tr("3.level3"), "3.level3Page", "2.levelPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::Airplane, tr("4.level1"), "4.level1Page", "3.level1Page");
    m_vNavView->insertIconTextItem(FluAwesomeType::Airplane, tr("4.level2"), "4.level2Page", "3.level1Page");
    m_vNavView->insertIconTextItem(FluAwesomeType::Airplane, tr("4.level3"), "4.level3Page", "3.level1Page");
    m_vNavView->insertIconTextItem(FluAwesomeType::Airplane, tr("5.level1"), "5.level1Page", "4.level3Page");
    m_vNavView->insertIconTextItem(FluAwesomeType::Airplane, tr("5.level2"), "5.level2Page", "4.level3Page");
    m_vNavView->insertIconTextItem(FluAwesomeType::Airplane, tr("5.level3"), "5.level3Page", "4.level3Page");
    m_vNavView->insertIconTextItem(FluAwesomeType::Airplane, tr("5.level4"), "5.level4Page", "4.level3Page");
}

void FluGalleryWindow::makeSamplesNavItem()
{
    makeSamplesHNavItem();
    makeSamplesVNavItem();

    auto allSamplesPage = new FluAllSamplesPage;
    m_layout->addWidget("AllSamplesPage", allSamplesPage);

    connect(allSamplesPage, &FluAllSamplesPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);
}

void FluGalleryWindow::makeSamplesHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::AllApps, tr("All samples"), "AllSamplesPage");
}

void FluGalleryWindow::makeSamplesVNavItem()
{
    m_vNavView->insertIconTextItem(FluAwesomeType::AllApps, tr("All samples"), "AllSamplesPage");
}

void FluGalleryWindow::makeBasicInputNavItem()
{
    makeBasicInputHNavItem();
    makeBasicInputVNavItem();

    auto basicInputPage = new FluBasicInputPage;
    m_layout->addWidget("BasicInputPage", basicInputPage);
    m_layout->addWidget("ButtonPage", new FluButtonPage);
    m_layout->addWidget("DropDownButtonPage", new FluDropDownButtonPage);
    m_layout->addWidget("HyperLinkButtonPage", new FluHyperLinkButtonPage);
    m_layout->addWidget("RepeatButtonPage", new FluRepeatButtonPage);
    m_layout->addWidget("ToggleButtonPage", new FluToggleButtonPage);
    m_layout->addWidget("SplitButtonPage", new FluSplitButtonPage);
    m_layout->addWidget("CheckBoxPage", new FluCheckBoxPage);
    m_layout->addWidget("ColorPickerPage", new FluColorPickerPage);
    m_layout->addWidget("ComboBoxPage", new FluComboBoxPage);
    m_layout->addWidget("RadioButtonPage", new FluRadioButtonPage);
    m_layout->addWidget("RatingControlPage", new FluRatingControlPage);
    m_layout->addWidget("SliderPage", new FluSliderPage);
    m_layout->addWidget("ToggleSwitchPage", new FluToggleSwitchPage);

    connect(basicInputPage, &FluBasicInputPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);
}

void FluGalleryWindow::makeBasicInputHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::CheckboxComposite, tr("Basic input"), "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("InputValidation"), "InputValidation", "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("Button"), "ButtonPage", "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("DropDownButton"), "DropDownButtonPage", "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("HyperLinkButton"), "HyperLinkButtonPage", "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("RepeatButton"), "RepeatButtonPage", "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("ToggleButton"), "ToggleButtonPage", "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("SplitButton"), "SplitButtonPage", "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("ToggleSplitButton"), "ToggleSplitButton", "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("CheckBox"), "CheckBoxPage", "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("ColorPicker"), "ColorPickerPage", "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("ComboBox"), "ComboBoxPage", "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("RadioButton"), "RadioButtonPage", "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("RatingControl"), "RatingControlPage", "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("Slider"), "SliderPage", "BasicInputPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("ToggleSwitch"), "ToggleSwitchPage", "BasicInputPage");
}

void FluGalleryWindow::makeBasicInputVNavItem()
{
    m_vNavView->insertIconTextItem(FluAwesomeType::CheckboxComposite, tr("Basic input"), "BasicInputPage");
    auto *inputValidation = m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("InputValidation"), "InputValidation", "BasicInputPage");
    inputValidation->enableThisItem(false);
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("Button"), "ButtonPage", "BasicInputPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("DropDownButton"), "DropDownButtonPage", "BasicInputPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("HyperLinkButton"), "HyperLinkButtonPage", "BasicInputPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("RepeatButton"), "RepeatButtonPage", "BasicInputPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("ToggleButton"), "ToggleButtonPage", "BasicInputPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("SplitButton"), "SplitButtonPage", "BasicInputPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("ToggleSplitButton"), "ToggleSplitButton", "BasicInputPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("CheckBox"), "CheckBoxPage", "BasicInputPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("ColorPicker"), "ColorPickerPage", "BasicInputPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("ComboBox"), "ComboBoxPage", "BasicInputPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("RadioButton"), "RadioButtonPage", "BasicInputPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("RatingControl"), "RatingControlPage", "BasicInputPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("Slider"), "SliderPage", "BasicInputPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("ToggleSwitch"), "ToggleSwitchPage", "BasicInputPage");
}

void FluGalleryWindow::makeCollectionsNavItem()
{
    makeCollectionsHNavItem();
    makeCollectionsVNavItem();

    auto collectionsPage = new FluCollectionsPage;
    m_layout->addWidget("CollectionsPage", collectionsPage);
    m_layout->addWidget("FlipViewPage", new FluFlipViewPage);
    m_layout->addWidget("ListViewPage", new FluListViewPage);
    m_layout->addWidget("TreeViewPage", new FluTreeViewPage);
    m_layout->addWidget("TableViewPage", new FluTableViewPage);

    connect(collectionsPage, &FluCollectionsPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);
}

void FluGalleryWindow::makeCollectionsHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::TiltDown, tr("Connections"), "CollectionsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("FlipView"), "FlipViewPage", "CollectionsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("ListView"), "ListViewPage", "CollectionsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("TreeView"), "TreeViewPage", "CollectionsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("TableView"), "TableViewPage", "CollectionsPage");
}

void FluGalleryWindow::makeCollectionsVNavItem()
{
    m_vNavView->insertIconTextItem(FluAwesomeType::TiltDown, tr("Connections"), "CollectionsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("FlipView"), "FlipViewPage", "CollectionsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("ListView"), "ListViewPage", "CollectionsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("TreeView"), "TreeViewPage", "CollectionsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("TableView"), "TableViewPage", "CollectionsPage");
}

void FluGalleryWindow::makDateTimeNavItem()
{
    makDateTimeHNavItem();
    makDateTimeVNavItem();

    auto dateAndTimePage = new FluDateAndTimePage;
    m_layout->addWidget("DateAndTimePage", dateAndTimePage);
    m_layout->addWidget("CalendarDatePickerPage", new FluCalendarDatePickerPage);
    m_layout->addWidget("CalendarViewPage", new FluCalendarViewPage);
    m_layout->addWidget("DatePickerPage", new FluDatePickerPage);
    m_layout->addWidget("TimePickerPage", new FluTimePickerPage);

    connect(dateAndTimePage, &FluDateAndTimePage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);
}

void FluGalleryWindow::makDateTimeHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::Calendar, tr("Date & time"), "DateAndTimePage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("CalendarDatePicker"), "CalendarDatePickerPage", "DateAndTimePage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("CalendarView"), "CalendarViewPage", "DateAndTimePage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("DatePicker"), "DatePickerPage", "DateAndTimePage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("TimePicker"), "TimePickerPage", "DateAndTimePage");
}

void FluGalleryWindow::makDateTimeVNavItem()
{
    m_vNavView->insertIconTextItem(FluAwesomeType::Calendar, tr("Date & time"), "DateAndTimePage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("CalendarDatePicker"), "CalendarDatePickerPage", "DateAndTimePage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("CalendarView"), "CalendarViewPage", "DateAndTimePage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("DatePicker"), "DatePickerPage", "DateAndTimePage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("TimePicker"), "TimePickerPage", "DateAndTimePage");
}

void FluGalleryWindow::makeDialogsFlyouts()
{
    makeDialogsFlyoutsHNavItem();
    makeDialogsFlyoutsVNavItem();

    auto dialogAndFlyoutPage = new FluDialogsAndFlyoutsPage;
    m_layout->addWidget("DialogsAndFlyoutsPage", dialogAndFlyoutPage);
    m_layout->addWidget("ContentDialogPage", new FluContentDialogPage);
    m_layout->addWidget("FlyoutPage", new FluFlyoutPage);

    connect(dialogAndFlyoutPage, &FluDialogsAndFlyoutsPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);
}

void FluGalleryWindow::makeDialogsFlyoutsHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::Comment, tr("Dialogs & flyouts"), "DialogsAndFlyoutsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("ContentDialog"), "ContentDialogPage", "DialogsAndFlyoutsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("Flyout"), "FlyoutPage", "DialogsAndFlyoutsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("TeachingTip"), "TeachingTipPage", "DialogsAndFlyoutsPage");
}

void FluGalleryWindow::makeDialogsFlyoutsVNavItem()
{
    m_vNavView->insertIconTextItem(FluAwesomeType::Comment, tr("Dialogs & flyouts"), "DialogsAndFlyoutsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("ContentDialog"), "ContentDialogPage", "DialogsAndFlyoutsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("Flyout"), "FlyoutPage", "DialogsAndFlyoutsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("TeachingTip"), "TeachingTipPage", "DialogsAndFlyoutsPage");
}

void FluGalleryWindow::makeLayoutNavItem()
{
    makeLayoutHNavItem();
    makeLayoutVNavItem();

    auto layoutPage = new FluLayoutPage;
    m_layout->addWidget("LayoutPage", layoutPage);
    m_layout->addWidget("BorderPage", new FluBorderPage);
    m_layout->addWidget("ExpanderPage", new FluExpanderPage);
    m_layout->addWidget("RadioButtonsPage", new FluRadioButtonsPage);

    connect(layoutPage, &FluLayoutPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);
}

void FluGalleryWindow::makeLayoutHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::PreviewLink, tr("Layout"), "LayoutPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("Border"), "BorderPage", "LayoutPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("Canvas"), "CanvasPage", "LayoutPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("Expander"), "ExpanderPage", "LayoutPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("ItemsRepeater"), "ItemsRepeaterPage", "LayoutPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("Grid"), "GridPage", "LayoutPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("RadioButtons"), "RadioButtonsPage", "LayoutPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("RelativePanel"), "RelativePanelPage", "LayoutPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("SplitView"), "SplitViewPage", "LayoutPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("StackPanel"), "StackPanelPage", "LayoutPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("VariableSizedWrapGrid"), "VariableSizedWrapGridPage", "LayoutPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("Viewbox"), "ViewboxPage", "LayoutPage");
}

void FluGalleryWindow::makeLayoutVNavItem()
{
    m_vNavView->insertIconTextItem(FluAwesomeType::PreviewLink, tr("Layout"), "LayoutPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("Border"), "BorderPage", "LayoutPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("Canvas"), "CanvasPage", "LayoutPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("Expander"), "ExpanderPage", "LayoutPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("ItemsRepeater"), "ItemsRepeaterPage", "LayoutPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("Grid"), "GridPage", "LayoutPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("RadioButtons"), "RadioButtonsPage", "LayoutPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("RelativePanel"), "RelativePanelPage", "LayoutPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("SplitView"), "SplitViewPage", "LayoutPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("StackPanel"), "StackPanelPage", "LayoutPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("VariableSizedWrapGrid"), "VariableSizedWrapGridPage", "LayoutPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("Viewbox"), "ViewboxPage", "LayoutPage");
}

void FluGalleryWindow::makeMediaNavItem()
{
    makeMediaHNavItem();
    makeMediaVNavItem();

    m_layout->addWidget("MediaPage", new FluMediaPage);
}

void FluGalleryWindow::makeMediaHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::Calendar, tr("Media"), "MediaPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("AnimatedVisualPlayer"), "AnimatedVisualPlayer", "MediaPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("Capture Element / Camera Preview"), "CaptureElement", "MediaPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("Image"), "Image", "MediaPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("mediaPalyerElement"), "MediaPlayerElement", "MediaPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("PersonPicture"), "PersonPicture", "MediaPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("Sound"), "Sound", "MediaPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("WebView2"), "WebView2", "MediaPage");
}

void FluGalleryWindow::makeMediaVNavItem()
{
    m_vNavView->insertIconTextItem(FluAwesomeType::Calendar, tr("Media"), "MediaPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("AnimatedVisualPlayer"), "AnimatedVisualPlayer", "MediaPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("Capture Element / Camera Preview"), "CaptureElement", "MediaPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("Image"), "Image", "MediaPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("mediaPalyerElement"), "MediaPlayerElement", "MediaPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("PersonPicture"), "PersonPicture", "MediaPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("Sound"), "Sound", "MediaPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("WebView2"), "WebView2", "MediaPage");
}

void FluGalleryWindow::makeSettingsNavItem()
{
    makeSettingsHNavItem();
    makeSettingsVNavItem();

    auto settingsPage = new FluSettingPage;
    m_layout->addWidget("SettingPage", settingsPage);
}

void FluGalleryWindow::makeSettingsHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::Settings, tr("Setting"), "SettingPage", FluHNavigationItemPosition::Right);
}

void FluGalleryWindow::makeSettingsVNavItem()
{
    FluVNavigationSettingsItem *item = new FluVNavigationSettingsItem(FluAwesomeType::Settings, tr("Setting"), this);
    item->setKey("SettingPage");
    m_vNavView->addItemToBottomLayout(item);
    connect(item, &FluVNavigationSettingsItem::itemClicked, [=]() { m_layout->setCurrentWidget("SettingPage"); });
}

void FluGalleryWindow::makeMenuToolBarsNavItem()
{
    makeMenuToolBarsHNavItem();
    makeMenuToolBarsVNavItem();

    auto menusAndToolBarsPage = new FluMenuAndToolBarsPage;
    m_layout->addWidget("MenusAndToolBarsPage", menusAndToolBarsPage);
    m_layout->addWidget("AppBarButtonPage", new FluAppBarButtonPage);
    m_layout->addWidget("AppBarToggleButtonPage", new FluAppBarToggleButtonPage);
    m_layout->addWidget("MenuBarPage", new FluMenuBarPage);

    connect(menusAndToolBarsPage, &FluMenuAndToolBarsPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);
}

void FluGalleryWindow::makeMenuToolBarsHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::Save, tr("Menus & toolbars"), "MenusAndToolBarsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("AppBarButton"), "AppBarButtonPage", "MenusAndToolBarsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("AppBarSeparator"), "AppBarSeparator", "MenusAndToolBarsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("AppBarToggleButton"), "AppBarToggleButtonPage", "MenusAndToolBarsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("CommandBar"), "CommandBarPage", "MenusAndToolBarsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("MenuBar"), "MenuBarPage", "MenusAndToolBarsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("CommandBarFlyout"), "CommandBarFlyoutPage", "MenusAndToolBarsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("MenuFlyout"), "MenuFlyoutPage", "MenusAndToolBarsPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("SwipeControl"), "SwipeControlPage", "MenusAndToolBarsPage");
}

void FluGalleryWindow::makeMenuToolBarsVNavItem()
{
    m_vNavView->insertIconTextItem(FluAwesomeType::Save, tr("Menus & toolbars"), "MenusAndToolBarsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("AppBarButton"), "AppBarButtonPage", "MenusAndToolBarsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("AppBarSeparator"), "AppBarSeparator", "MenusAndToolBarsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("AppBarToggleButton"), "AppBarToggleButtonPage", "MenusAndToolBarsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("CommandBar"), "CommandBarPage", "MenusAndToolBarsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("MenuBar"), "MenuBarPage", "MenusAndToolBarsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("CommandBarFlyout"), "CommandBarFlyoutPage", "MenusAndToolBarsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("MenuFlyout"), "MenuFlyoutPage", "MenusAndToolBarsPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("SwipeControl"), "SwipeControlPage", "MenusAndToolBarsPage");
}

void FluGalleryWindow::makeNavigationNavItem()
{
    makeNavigationHNavItem();
    makeNavigationVNavItem();

    auto navigationPage = new FluNavigationPage;
    m_layout->addWidget("NavigationPage", navigationPage);
    m_layout->addWidget("PivotPage", new FluPivotPage);

    connect(navigationPage, &FluNavigationPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);
}

void FluGalleryWindow::makeNavigationHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::BookmarksMirrored, tr("Navigation"), "NavigationPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("BreadcrumbBar"), "BreadcrumbBarPage", "NavigationPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("NavigationView"), "NavigationViewPage", "NavigationPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("Pivot"), "PivotPage", "NavigationPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("TabView"), "TabViewPage", "NavigationPage");
}

void FluGalleryWindow::makeNavigationVNavItem()
{
    m_vNavView->insertIconTextItem(FluAwesomeType::BookmarksMirrored, tr("Navigation"), "NavigationPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("BreadcrumbBar"), "BreadcrumbBarPage", "NavigationPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("NavigationView"), "NavigationViewPage", "NavigationPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("Pivot"), "PivotPage", "NavigationPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("TabView"), "TabViewPage", "NavigationPage");
}

void FluGalleryWindow::makeScrollingNavItem()
{
    makeScrollingHNavItem();
    makeScrollingVNavItem();

    auto scrollingPage = new FluScrollingPage;
    m_layout->addWidget("ScrollingPage", scrollingPage);
    m_layout->addWidget("ScrollViewPage", new FluScrollViewPage);

    connect(scrollingPage, &FluScrollingPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);
}

void FluGalleryWindow::makeScrollingHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::Sort, tr("Scrolling"), "ScrollingPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("AnnotatedScrollBar"), "AnnotatedScrollBar", "ScrollingPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("PipsPager"), "PipsPager", "ScrollingPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("ScrollView"), "ScrollViewPage", "ScrollingPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("ScrollViewer"), "ScrollViewer", "ScrollingPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("SemanticZoom"), "SemanticZoom", "ScrollingPage");
}

void FluGalleryWindow::makeScrollingVNavItem()
{
    m_vNavView->insertIconTextItem(FluAwesomeType::Sort, tr("Scrolling"), "ScrollingPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("AnnotatedScrollBar"), "AnnotatedScrollBar", "ScrollingPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("PipsPager"), "PipsPager", "ScrollingPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("ScrollView"), "ScrollViewPage", "ScrollingPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("ScrollViewer"), "ScrollViewer", "ScrollingPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("SemanticZoom"), "SemanticZoom", "ScrollingPage");
}

void FluGalleryWindow::makeStatusInfoNavItem()
{
    makeStatusInfoHNavItem();
    makeStatusInfoVNavItem();

    auto statusAndInfoPage = new FluStatusAndInfoPage;
    m_layout->addWidget("StatusAndInfoPage", statusAndInfoPage);
    m_layout->addWidget("InfoBadgePage", new FluInfoBadgePage);
    m_layout->addWidget("InfoBarPage", new FluInfoBarPage);
    m_layout->addWidget("ProgressBarPage", new FluProgressBarPage);
    m_layout->addWidget("ProgressRingPage", new FluProgressRingPage);

    connect(statusAndInfoPage, &FluStatusAndInfoPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);
}

void FluGalleryWindow::makeStatusInfoHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::Reminder, tr("Status & info"), "StatusAndInfoPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("InfoBadge"), "InfoBadgePage", "StatusAndInfoPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("InfoBar"), "InfoBarPage", "StatusAndInfoPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("ProgressBar"), "ProgressBarPage", "StatusAndInfoPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("ProgressRing"), "ProgressRingPage", "StatusAndInfoPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("ToolTip"), "ToolTip", "StatusAndInfoPage");
}

void FluGalleryWindow::makeStatusInfoVNavItem()
{
    m_vNavView->insertIconTextItem(FluAwesomeType::Reminder, tr("Status & info"), "StatusAndInfoPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("InfoBadge"), "InfoBadgePage", "StatusAndInfoPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("InfoBar"), "InfoBarPage", "StatusAndInfoPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("ProgressBar"), "ProgressBarPage", "StatusAndInfoPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("ProgressRing"), "ProgressRingPage", "StatusAndInfoPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("ToolTip"), "ToolTip", "StatusAndInfoPage");
}

void FluGalleryWindow::makeTextNavItem()
{
    makeTextHNavItem();
    makeTextVNavItem();

    auto textPage = new FluTextPage;
    m_layout->addWidget("TextPage", textPage);
    m_layout->addWidget("AutoSuggestBoxPage", new FluAutoSuggestBoxPage);
    m_layout->addWidget("NumberBoxPage", new FluNumberBoxPage);
    m_layout->addWidget("PasswordBoxPage", new FluPasswordBoxPage);
    m_layout->addWidget("TextBoxPage", new FluTextBoxPage);

    connect(textPage, &FluTextPage::clickedHCard, this, &FluGalleryWindow::onClickedHCard);
}

void FluGalleryWindow::makeTextHNavItem()
{
    m_hNavView->insertIconTextItem(FluAwesomeType::Font, tr("Text"), "TextPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("AutoSuggestBox"), "AutoSuggestBoxPage", "TextPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("NumberBox"), "NumberBoxPage", "TextPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("PasswordBox"), "PasswordBoxPage", "TextPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("RichEditBox"), "RichEditBoxPage", "TextPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("RichTextBlock"), "RichTextBlockPage", "TextPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("TextBlock"), "TextBlockPage", "TextPage");
    m_hNavView->insertIconTextItem(FluAwesomeType::None, tr("TextBox"), "TextBoxPage", "TextPage");
}

void FluGalleryWindow::makeTextVNavItem()
{
    m_vNavView->insertIconTextItem(FluAwesomeType::Font, tr("Text"), "TextPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("AutoSuggestBox"), "AutoSuggestBoxPage", "TextPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("NumberBox"), "NumberBoxPage", "TextPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("PasswordBox"), "PasswordBoxPage", "TextPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("RichEditBox"), "RichEditBoxPage", "TextPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("RichTextBlock"), "RichTextBlockPage", "TextPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("TextBlock"), "TextBlockPage", "TextPage");
    m_vNavView->insertIconTextItem(FluAwesomeType::None, tr("TextBox"), "TextBoxPage", "TextPage");
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
        FluConfigUtils::getUtils()->setNavWidth(m_vNavView->getViewWidth());
        FluConfigUtils::getUtils()->setNavStyle(m_isHorizontalNav ? 1 : 0);
        FluConfigUtils::getUtils()->setViewCollapsed(!m_vNavView->isLong());
        QApplication::quit();
    }
}

void FluGalleryWindow::onClickedHCard(QString key)
{
    auto item = m_vNavView->getItemByKey(key);
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
