#pragma once

#include "../FluControls/FluFrameLessWidget.h"
#include "../FluControls/FluNavigationView.h"
#include "FluHomePage.h"
#include <QStackedLayout>

class FluGalleryWindow : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    FluGalleryWindow(QWidget *parent = nullptr);

    void makeHomeNavItem()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::Home), "Home", this);
        m_navView->addNavigationItemMid(item);
    }

    void makeDesignGuidanceNavItem()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::Design), "Design guidance", this);
        FluNavigationItem *item1 = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::FontSize), "Typography", item);
        FluNavigationItem *item2 = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::EmojiTabSymbols), "Icons", item);
        FluNavigationItem *item3 = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::Color), "Colors", item);

        item->addChildItem(item1);
        item->addChildItem(item2);
        item->addChildItem(item3);
        m_navView->addNavigationItemMid(item);
    }

    void makeSamplesNavItem()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::AllApps), "All samples", this);
        m_navView->addNavigationItemMid(item);
    }

    void makeBasicInputNavItem()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::CheckboxComposite), "Basic input", this);

        FluNavigationItem *item1 = new FluNavigationItem("InputValidation", item);
        FluNavigationItem *item2 = new FluNavigationItem("Button", item);
        FluNavigationItem *item3 = new FluNavigationItem("DropDownButton", item);

        FluNavigationItem *item4 = new FluNavigationItem("HyperLinkButton", item);
        FluNavigationItem *item5 = new FluNavigationItem("RepeatButton", item);
        FluNavigationItem *item6 = new FluNavigationItem("ToggleButton", item);

        FluNavigationItem *item7 = new FluNavigationItem("SplitButton", item);
        FluNavigationItem *item8 = new FluNavigationItem("ToggleSplitButton", item);
        FluNavigationItem *item9 = new FluNavigationItem("CheckBox", item);

        FluNavigationItem *item10 = new FluNavigationItem("CheckBox", item);
        FluNavigationItem *item11 = new FluNavigationItem("ComboBox", item);
        FluNavigationItem *item12 = new FluNavigationItem("RadioButton", item);

        FluNavigationItem *item13 = new FluNavigationItem("RatingControl", item);
        FluNavigationItem *item14 = new FluNavigationItem("Slider", item);
        FluNavigationItem *item15 = new FluNavigationItem("ToggleSwith", item);

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

    void makeCollectionsNavItem()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::TiltDown), "Connections", this);
        FluNavigationItem *item1 = new FluNavigationItem("FlipView", item);
        FluNavigationItem *item2 = new FluNavigationItem("GridView", item);
        FluNavigationItem *item3 = new FluNavigationItem("ItemsView", item);
        FluNavigationItem *item4 = new FluNavigationItem("ListBox", item);
        FluNavigationItem *item5 = new FluNavigationItem("ListView", item);
        FluNavigationItem *item6 = new FluNavigationItem("PullToRefresh", item);
        FluNavigationItem *item7 = new FluNavigationItem("TreeView", item);
        FluNavigationItem *item8 = new FluNavigationItem("DataGrid", item);
        item->addChildItem(item1);
        item->addChildItem(item2);
        item->addChildItem(item3);
        item->addChildItem(item4);
        item->addChildItem(item5);
        item->addChildItem(item6);
        item->addChildItem(item7);
        item->addChildItem(item8);
        m_navView->addNavigationItemMid(item);
    }

    void makDateTimeNavItem()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::Calendar), "Date & time", this);
        FluNavigationItem *item1 = new FluNavigationItem("CalendarDatePicker", item);
        FluNavigationItem *item2 = new FluNavigationItem("CalendarView", item);
        FluNavigationItem *item3 = new FluNavigationItem("DatePicker", item);
        FluNavigationItem *item4 = new FluNavigationItem("TimePicker", item);
        item->addChildItem(item1);
        item->addChildItem(item2);
        item->addChildItem(item3);
        item->addChildItem(item4);
        m_navView->addNavigationItemMid(item);
    }
    
    void makeDialogsFlyouts()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::Comment), "Dialogs & flyouts", this);
        FluNavigationItem *item1 = new FluNavigationItem("ContentDialog", item);
        FluNavigationItem *item2 = new FluNavigationItem("Flyout", item);
        FluNavigationItem *item3 = new FluNavigationItem("TeachingTip", item);
        item->addChildItem(item1);
        item->addChildItem(item2);
        item->addChildItem(item3);
        m_navView->addNavigationItemMid(item);
    }

    void makeLayoutNavItem()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::PreviewLink), "Layout", this);
        FluNavigationItem *item1 = new FluNavigationItem("Border", item);
        FluNavigationItem *item2 = new FluNavigationItem("Canvas", item);
        FluNavigationItem *item3 = new FluNavigationItem("Expander", item);
        FluNavigationItem *item4 = new FluNavigationItem("ItemsRepeater", item);
        FluNavigationItem *item5 = new FluNavigationItem("Grid", item);
        FluNavigationItem *item6 = new FluNavigationItem("RadioButtons", item);
        FluNavigationItem *item7 = new FluNavigationItem("RelativePanel", item);
        FluNavigationItem *item8 = new FluNavigationItem("SplitView", item);
        FluNavigationItem *item9 = new FluNavigationItem("StackPanel", item);
        FluNavigationItem *item10 = new FluNavigationItem("VariableSizedWrapGrid", item);
        FluNavigationItem *item11 = new FluNavigationItem("ViewBox", item);

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
        m_navView->addNavigationItemMid(item);
    }

    void makeMediaNavItem()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::Calendar), "Media", this);
        FluNavigationItem *item1 = new FluNavigationItem("AnimatedVisualPlayer", item);
        FluNavigationItem *item2 = new FluNavigationItem("Capture Element / Camera Preview", item);
        FluNavigationItem *item3 = new FluNavigationItem("Image", item);
        FluNavigationItem *item4 = new FluNavigationItem("mediaPalyerElement", item);
        FluNavigationItem *item5 = new FluNavigationItem("PersonPicture", item);
        FluNavigationItem *item6 = new FluNavigationItem("Sound", item);
        FluNavigationItem *item7 = new FluNavigationItem("WebView2", item);

        item->addChildItem(item1);
        item->addChildItem(item2);
        item->addChildItem(item3);
        item->addChildItem(item4);
        item->addChildItem(item5);
        item->addChildItem(item6);
        item->addChildItem(item7);
        m_navView->addNavigationItemMid(item);
    }

    void makeSettingsNavItem()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::Settings), "Setting", this);
        m_navView->addNavigationItemButtom(item);
    }

    void makeMenuToolBarsNavItem()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::Save), "Menus & toolbars", this);
        FluNavigationItem *item1 = new FluNavigationItem("XamlUICommand", item);
        FluNavigationItem *item2 = new FluNavigationItem("StandardUICommand", item);
        FluNavigationItem *item3 = new FluNavigationItem("AppBarButton", item);
        FluNavigationItem *item4 = new FluNavigationItem("AppBarSeparator", item);
        FluNavigationItem *item5 = new FluNavigationItem("AppBarToggleButton", item);
        FluNavigationItem *item6 = new FluNavigationItem("CommandBar", item);
        FluNavigationItem *item7 = new FluNavigationItem("MenuBar", item);
        FluNavigationItem *item8 = new FluNavigationItem("CommandBarFlyout", item);
        FluNavigationItem *item9 = new FluNavigationItem("MenuFlyout", item);
        FluNavigationItem *item10 = new FluNavigationItem("SwipeControl", item);

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
        m_navView->addNavigationItemMid(item);
    }
   
    void makeNavigationNavItem()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::GlobalNavButton), "Navigation", this);
        FluNavigationItem *item1 = new FluNavigationItem("BreadcrumbBar", item);
        FluNavigationItem *item2 = new FluNavigationItem("NavigationView", item);
        FluNavigationItem *item3 = new FluNavigationItem("Pivot", item);
        FluNavigationItem *item4 = new FluNavigationItem("TabView", item);

        item->addChildItem(item1);
        item->addChildItem(item2);
        item->addChildItem(item3);
        item->addChildItem(item4);
        m_navView->addNavigationItemMid(item);
    }

    void makeScrollingNavItem()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::Calendar), "Scrolling", this);
        FluNavigationItem *item1 = new FluNavigationItem("AnnotatedScrollBar", item);
        FluNavigationItem *item2 = new FluNavigationItem("PipsPager", item);
        FluNavigationItem *item3 = new FluNavigationItem("ScrollView", item);
        FluNavigationItem *item4 = new FluNavigationItem("ScrollViewer", item);
        FluNavigationItem *item5 = new FluNavigationItem("SemanticZoom", item);

        item->addChildItem(item1);
        item->addChildItem(item2);
        item->addChildItem(item3);
        item->addChildItem(item4);
        item->addChildItem(item5);
        m_navView->addNavigationItemMid(item);
    }

    void makeStatusInfoNavItem()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::Calendar), "Status & info", this);
        FluNavigationItem *item1 = new FluNavigationItem("InfoBadge", item);
        FluNavigationItem *item2 = new FluNavigationItem("InfoBar", item);
        FluNavigationItem *item3 = new FluNavigationItem("progressBar", item);
        FluNavigationItem *item4 = new FluNavigationItem("progressRing", item);
        FluNavigationItem *item5 = new FluNavigationItem("ToolTip", item);

        item->addChildItem(item1);
        item->addChildItem(item2);
        item->addChildItem(item3);
        item->addChildItem(item4);
        item->addChildItem(item5);
        m_navView->addNavigationItemMid(item);
    }

    void makeTextNavItem()
    {
        FluNavigationItem *item = new FluNavigationItem(FluIconUtils::getFluentIcon(FluAwesomeType::Font), "Text", this);
        FluNavigationItem *item1 = new FluNavigationItem("AutoSuggestBox", item);
        FluNavigationItem *item2 = new FluNavigationItem("NumberBox", item);
        FluNavigationItem *item3 = new FluNavigationItem("PassWordBox", item);
        FluNavigationItem *item4 = new FluNavigationItem("RichEditBox", item);
        FluNavigationItem *item5 = new FluNavigationItem("RichTextBlock", item);
        FluNavigationItem *item6 = new FluNavigationItem("TextBlock", item);
        FluNavigationItem *item7 = new FluNavigationItem("TextBox", item);

        item->addChildItem(item1);
        item->addChildItem(item2);
        item->addChildItem(item3);
        item->addChildItem(item4);
        item->addChildItem(item5);
        item->addChildItem(item6);
        item->addChildItem(item7);
        m_navView->addNavigationItemMid(item);
    }

  protected:
    FluNavigationView *m_navView;
    QStackedLayout *m_sLayout;
};
