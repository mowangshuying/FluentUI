#pragma once

#include "../FluControls/FluFrameLessWidget.h"
#include "../FluControls/FluNavigationView.h"
#include "../FluControls/FluNavigationIconTextItem.h"
#include "FluHomePage.h"
#include <QStackedLayout>
#include "../FluControls/FluStackedLayout.h"
#include "FluTypeographyPage.h"
#include "../FluControls/FluNavigationSettingsItem.h"
#include "FluIconsPage.h"
#include "FluButtonPage.h"
#include "FluToggleButtonPage.h"
#include "FluDropDownButtonPage.h"
#include "FluHyperLinkButtonPage.h"
#include "FluSettingPage.h"
#include "FluRepeatButtonPage.h"
#include "FluRadioButtonPage.h"
#include "FluAllSamplesPage.h"
#include "FluCheckBoxPage.h"
#include "FluSliderPage.h"
#include "FluProgressRingPage.h"
#include "FluCalendarViewPage.h"
#include "FluProgressBarPage.h"
#include "FluFlipViewPage.h"
#include "FluListViewPage.h"
#include "FluExpanderPage.h"
#include "FluCalendarDatePickerPage.h"
#include "FluCollectionsPage.h"
#include "FluPasswordBoxPage.h"
#include "../FluControls/FluMessageBox.h"
#include "FluComboBoxPage.h"
#include "FluContentDialogPage.h"

class FluGalleryWindow : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    FluGalleryWindow(QWidget *parent = nullptr);

    void makeHomeNavItem()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::Home, "Home", this);
        m_navView->addItemToMidLayout(item);

        auto homePage = new FluHomePage;
        m_sLayout->addWidget("HomePage", homePage);
        connect(item, &FluNavigationIconTextItem::itemClicked, [=]() {
            m_sLayout->setCurrentWidget("HomePage");

            FluMessageBox messageBox("Close Gallery Window?", "choose \"Ok\" to close. choose \"Cancel\" do nothing.", this);
            int nExec = messageBox.exec();
        });
    }

    void makeDesignGuidanceNavItem()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::Design, "Design guidance", this);
        FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem(FluAwesomeType::FontSize, "Typography", item);
        FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem(FluAwesomeType::EmojiTabSymbols, "Icons", item);
        // FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem(FluAwesomeType::Color, "Colors", item);

        item->addItem(item1);
        item->addItem(item2);
        // item->addItem(item3);
        m_navView->addItemToMidLayout(item);

        auto typographyPage = new FluTypeographyPage;
        m_sLayout->addWidget("TypographyPage", typographyPage);
        connect(item1, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("TypographyPage"); });

        auto iconsPage = new FluIconsPage;
        m_sLayout->addWidget("IconsPage", iconsPage);
        connect(item2, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("IconsPage"); });
    }

    void makeSamplesNavItem()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::AllApps, "All samples", this);
        m_navView->addItemToMidLayout(item);

        auto allSamplesPage = new FluAllSamplesPage;
        m_sLayout->addWidget("AllSamplesPage", allSamplesPage);
        connect(item, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("AllSamplesPage"); });
    }

    void makeBasicInputNavItem()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::CheckboxComposite, "Basic input", this);

        FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem("InputValidation", item);
        item1->enableThisItem(false);

        FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem("Button", item);
        auto buttonPage = new FluButtonPage;
        m_sLayout->addWidget("ButtonPage", buttonPage);
        connect(item2, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ButtonPage"); });

        FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem("DropDownButton", item);
        auto dropDownPage = new FluDropDownButtonPage;
        m_sLayout->addWidget("DropDownButtonPage", dropDownPage);
        connect(item3, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("DropDownButtonPage"); });

        FluNavigationIconTextItem *item4 = new FluNavigationIconTextItem("HyperLinkButton", item);
        auto hyperLinkButtonPage = new FluHyperLinkButtonPage;
        m_sLayout->addWidget("HyperLinkButtonPage", hyperLinkButtonPage);
        connect(item4, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("HyperLinkButtonPage"); });

        FluNavigationIconTextItem *item5 = new FluNavigationIconTextItem("RepeatButton", item);
        auto repeatButtonPage = new FluRepeatButtonPage;
        m_sLayout->addWidget("RepeatButtonPage", repeatButtonPage);
        connect(item5, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("RepeatButtonPage"); });

        FluNavigationIconTextItem *item6 = new FluNavigationIconTextItem("ToggleButton", item);
        auto toggleButtonPage = new FluToggleButtonPage;
        m_sLayout->addWidget("ToggleButtonPage", toggleButtonPage);
        connect(item6, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ToggleButtonPage"); });

        FluNavigationIconTextItem *item7 = new FluNavigationIconTextItem("SplitButton", item);
        FluNavigationIconTextItem *item8 = new FluNavigationIconTextItem("ToggleSplitButton", item);

        FluNavigationIconTextItem *item9 = new FluNavigationIconTextItem("CheckBox", item);
        auto checkBoxPage = new FluCheckBoxPage;
        m_sLayout->addWidget("CheckBoxPage", checkBoxPage);
        connect(item9, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("CheckBoxPage"); });

        FluNavigationIconTextItem *item10 = new FluNavigationIconTextItem("ColorPicker", item);

        FluNavigationIconTextItem *item11 = new FluNavigationIconTextItem("ComboBox", item);
        auto comboBoxPage = new FluComboBoxPage;
        m_sLayout->addWidget("ComboBoxPage", comboBoxPage);
        connect(item11, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ComboBoxPage"); });

        FluNavigationIconTextItem *item12 = new FluNavigationIconTextItem("RadioButton", item);
        auto radioButtonPage = new FluRadioButtonPage;
        m_sLayout->addWidget("RadioButtonPage", radioButtonPage);
        connect(item12, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("RadioButtonPage"); });

        FluNavigationIconTextItem *item13 = new FluNavigationIconTextItem("RatingControl", item);

        FluNavigationIconTextItem *item14 = new FluNavigationIconTextItem("Slider", item);
        auto sliderPage = new FluSliderPage;
        m_sLayout->addWidget("SliderPage", sliderPage);
        connect(item14, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("SliderPage"); });

        FluNavigationIconTextItem *item15 = new FluNavigationIconTextItem("ToggleSwith", item);

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
    }

    void makeCollectionsNavItem()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::TiltDown, "Connections", this);
        auto collectionsPage = new FluCollectionsPage;
        m_sLayout->addWidget("CollectionsPage", collectionsPage);
        connect(item, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("CollectionsPage"); });

        FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem("FlipView", item);
        auto flipViewPage = new FluFlipViewPage;
        m_sLayout->addWidget("FlipViewPage", flipViewPage);
        connect(item1, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("FlipViewPage"); });

        // FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem("GridView", item);
        // FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem("ItemsView", item);
        // FluNavigationIconTextItem *item4 = new FluNavigationIconTextItem("ListBox", item);

        FluNavigationIconTextItem *item5 = new FluNavigationIconTextItem("ListView", item);
        auto listViewPage = new FluListViewPage;
        m_sLayout->addWidget("ListViewPage", listViewPage);
        connect(item5, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ListViewPage"); });

        // FluNavigationIconTextItem *item6 = new FluNavigationIconTextItem("PullToRefresh", item);
        FluNavigationIconTextItem *item7 = new FluNavigationIconTextItem("TreeView", item);
        // FluNavigationIconTextItem *item8 = new FluNavigationIconTextItem("DataGrid", item);
        item->addItem(item1);
        // item->addItem(item2);
        // item->addItem(item3);
        // item->addItem(item4);
        item->addItem(item5);
        // item->addItem(item6);
        item->addItem(item7);
        //  item->addItem(item8);
        m_navView->addItemToMidLayout(item);
    }

    void makDateTimeNavItem()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::Calendar, "Date & time", this);

        FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem("CalendarDatePickerPage", item);
        auto calendarDatePickerPage = new FluCalendarDatePickerPage;
        m_sLayout->addWidget("CalendarDatePickerPage", calendarDatePickerPage);
        connect(item1, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("CalendarDatePickerPage"); });

        FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem("CalendarView", item);
        auto calendarViewPage = new FluCalendarViewPage;
        m_sLayout->addWidget("CalendarViewPage", calendarViewPage);
        connect(item2, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("CalendarViewPage"); });

        FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem("DatePicker", item);
        FluNavigationIconTextItem *item4 = new FluNavigationIconTextItem("TimePicker", item);
        item->addItem(item1);
        item->addItem(item2);
        item->addItem(item3);
        item->addItem(item4);
        m_navView->addItemToMidLayout(item);
    }

    void makeDialogsFlyouts()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::Comment, "Dialogs & flyouts", this);
        FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem("ContentDialog", item);
        
        auto contentDialogPage = new FluContentDialogPage;
        m_sLayout->addWidget("ContentDialogPage", contentDialogPage);
        connect(item1, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ContentDialogPage"); });


        FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem("Flyout", item);
        FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem("TeachingTip", item);
        item->addItem(item1);
        item->addItem(item2);
        item->addItem(item3);
        m_navView->addItemToMidLayout(item);
    }

    void makeLayoutNavItem()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::PreviewLink, "Layout", this);
        FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem("Border", item);
        FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem("Canvas", item);

        FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem("Expander", item);
        auto expanderPage = new FluExpanderPage;
        m_sLayout->addWidget("ExpanderPage", expanderPage);
        connect(item3, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ExpanderPage"); });

        FluNavigationIconTextItem *item4 = new FluNavigationIconTextItem("ItemsRepeater", item);
        FluNavigationIconTextItem *item5 = new FluNavigationIconTextItem("Grid", item);
        FluNavigationIconTextItem *item6 = new FluNavigationIconTextItem("RadioButtons", item);
        FluNavigationIconTextItem *item7 = new FluNavigationIconTextItem("RelativePanel", item);
        FluNavigationIconTextItem *item8 = new FluNavigationIconTextItem("SplitView", item);
        FluNavigationIconTextItem *item9 = new FluNavigationIconTextItem("StackPanel", item);
        FluNavigationIconTextItem *item10 = new FluNavigationIconTextItem("VariableSizedWrapGrid", item);
        FluNavigationIconTextItem *item11 = new FluNavigationIconTextItem("ViewBox", item);

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
    }

    void makeMediaNavItem()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::Calendar, "Media", this);
        FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem("AnimatedVisualPlayer", item);
        FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem("Capture Element / Camera Preview", item);
        FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem("Image", item);
        FluNavigationIconTextItem *item4 = new FluNavigationIconTextItem("mediaPalyerElement", item);
        FluNavigationIconTextItem *item5 = new FluNavigationIconTextItem("PersonPicture", item);
        FluNavigationIconTextItem *item6 = new FluNavigationIconTextItem("Sound", item);
        FluNavigationIconTextItem *item7 = new FluNavigationIconTextItem("WebView2", item);

        item->addItem(item1);
        item->addItem(item2);
        item->addItem(item3);
        item->addItem(item4);
        item->addItem(item5);
        item->addItem(item6);
        item->addItem(item7);
        m_navView->addItemToMidLayout(item);
    }

    void makeSettingsNavItem()
    {
        FluNavigationSettingsItem *item = new FluNavigationSettingsItem(FluAwesomeType::Settings, "Setting", this);
        m_navView->addItemToBottomLayout(item);

        auto settingsPage = new FluSettingPage;
        m_sLayout->addWidget("SettingPage", settingsPage);
        connect(item, &FluNavigationSettingsItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("SettingPage"); });
    }

    void makeMenuToolBarsNavItem()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::Save, "Menus & toolbars", this);
        FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem("XamlUICommand", item);
        FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem("StandardUICommand", item);
        FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem("AppBarButton", item);
        FluNavigationIconTextItem *item4 = new FluNavigationIconTextItem("AppBarSeparator", item);
        FluNavigationIconTextItem *item5 = new FluNavigationIconTextItem("AppBarToggleButton", item);
        FluNavigationIconTextItem *item6 = new FluNavigationIconTextItem("CommandBar", item);
        FluNavigationIconTextItem *item7 = new FluNavigationIconTextItem("MenuBar", item);
        FluNavigationIconTextItem *item8 = new FluNavigationIconTextItem("CommandBarFlyout", item);
        FluNavigationIconTextItem *item9 = new FluNavigationIconTextItem("MenuFlyout", item);
        FluNavigationIconTextItem *item10 = new FluNavigationIconTextItem("SwipeControl", item);

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
        m_navView->addItemToMidLayout(item);
    }

    void makeNavigationNavItem()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::BookmarksMirrored, "Navigation", this);
        FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem("BreadcrumbBar", item);
        FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem("NavigationView", item);
        FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem("Pivot", item);
        FluNavigationIconTextItem *item4 = new FluNavigationIconTextItem("TabView", item);

        item->addItem(item1);
        item->addItem(item2);
        item->addItem(item3);
        item->addItem(item4);
        m_navView->addItemToMidLayout(item);
    }

    void makeScrollingNavItem()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::Sort, "Scrolling", this);
        FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem("AnnotatedScrollBar", item);
        FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem("PipsPager", item);
        FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem("ScrollView", item);
        FluNavigationIconTextItem *item4 = new FluNavigationIconTextItem("ScrollViewer", item);
        FluNavigationIconTextItem *item5 = new FluNavigationIconTextItem("SemanticZoom", item);

        item->addItem(item1);
        item->addItem(item2);
        item->addItem(item3);
        item->addItem(item4);
        item->addItem(item5);
        m_navView->addItemToMidLayout(item);
    }

    void makeStatusInfoNavItem()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::Reminder, "Status & info", this);
        FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem("InfoBadge", item);
        FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem("InfoBar", item);

        FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem("progressBar", item);
        auto progressBarPage = new FluProgressBarPage;
        m_sLayout->addWidget("ProgressBarPage", progressBarPage);
        connect(item3, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ProgressBarPage"); });

        FluNavigationIconTextItem *item4 = new FluNavigationIconTextItem("progressRing", item);

        auto progressRingPage = new FluProgressRingPage;
        m_sLayout->addWidget("ProgressRingPage", progressRingPage);
        connect(item4, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ProgressRingPage"); });

        FluNavigationIconTextItem *item5 = new FluNavigationIconTextItem("ToolTip", item);

        item->addItem(item1);
        item->addItem(item2);
        item->addItem(item3);
        item->addItem(item4);
        item->addItem(item5);
        m_navView->addItemToMidLayout(item);
    }

    void makeTextNavItem()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::Font, "Text", this);
        FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem("AutoSuggestBox", item);
        FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem("NumberBox", item);

        FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem("PassWordBox", item);
        auto passwordBoxPage = new FluPasswordBoxPage;
        m_sLayout->addWidget("PasswordBoxPage", passwordBoxPage);
        connect(item3, &FluNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("PasswordBoxPage"); });

        FluNavigationIconTextItem *item4 = new FluNavigationIconTextItem("RichEditBox", item);
        FluNavigationIconTextItem *item5 = new FluNavigationIconTextItem("RichTextBlock", item);
        FluNavigationIconTextItem *item6 = new FluNavigationIconTextItem("TextBlock", item);
        FluNavigationIconTextItem *item7 = new FluNavigationIconTextItem("TextBox", item);

        item->addItem(item1);
        item->addItem(item2);
        item->addItem(item3);
        item->addItem(item4);
        item->addItem(item5);
        item->addItem(item6);
        item->addItem(item7);
        m_navView->addItemToMidLayout(item);
    }

    void resizeEvent(QResizeEvent *event)
    {
        // if (event->size().width() == width())
        //     return;

        if (width() > 1000)
        {
            // check it
            if (!m_navView->isLong())
                m_navView->onMenuItemClicked();
        }
        else
        {
            if (m_navView->isLong())
                m_navView->onMenuItemClicked();
        }
    }

    void closeEvent(QCloseEvent *event);
  public slots:
    void onThemeChanged();

  protected:
    FluNavigationView *m_navView;
    FluStackedLayout *m_sLayout;
};
