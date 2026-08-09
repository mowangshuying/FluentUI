#pragma once

#include "../controls/FluFrameLessWidget.h"
#include "../controls/FluVNavigationView.h"
#include "../controls/FluVNavigationIconTextItem.h"
#include "../controls/FluHNavigationView.h"
#include "../controls/FluHNavigationIconTextItem.h"
#include "FluHomePage.h"
#include <QStackedLayout>
#include "../controls/FluStackedLayout.h"
#include "FluTypeographyPage.h"
#include "../controls/FluVNavigationSettingsItem.h"
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
#include "../controls/FluMessageBox.h"
#include "FluComboBoxPage.h"
#include "FluContentDialogPage.h"
#include <QPainter>
#include <QStyleOption>
#include "FluMenuBarPage.h"
#include "FluNumberBoxPage.h"
#include "FluInfoBadgePage.h"
#include "FluToolTipPage.h"
#include "FluInfoBarPage.h"
#include "FluBorderPage.h"
#include "FluRadioButtonsPage.h"
#include "FluPivotPage.h"
#include "FluFlyoutPage.h"
#include "FluToggleSwitchPage.h"
#include "FluTextBoxPage.h"
#include "FluRatingControlPage.h"
#include "FluTimePickerPage.h"
#include "FluDatePickerPage.h"
#include "FluDateAndTimePage.h"
#include "FluDialogsAndFlyoutsPage.h"
#include "FluStatusAndInfoPage.h"
#include "FluAutoSuggestBoxPage.h"
#include "FluTextPage.h"
#include "FluSplitButtonPage.h"
#include "FluAppBarButtonPage.h"
#include "FluAppBarToggleButtonPage.h"
#include "FluLayoutPage.h"
#include "FluMenuAndToolBarsPage.h"
#include "FluMediaPage.h"
#include "FluScrollingPage.h"
#include "FluNavigationPage.h"
#include "FluBasicInputPage.h"
#include "FluScrollViewPage.h"
#include "FluTableViewPage.h"
#include "FluTreeViewPage.h"
#include "../controls/FluWindowKitWidget.h"
#include "FluColorPickerPage.h"

// #define USE_WINDOWKIT_WIDGET
#if !defined USE_WINDOWKIT_WIDGET
class FluGalleryWindow : public FluFrameLessWidget
#else
class FluGalleryWindow : public FluWindowKitWidget
#endif
{
    Q_OBJECT
  public:
    FluGalleryWindow(QWidget *parent = nullptr);

    void switchNavigationStyle(int index);
    void animateNavSwitch(bool toHorizontal);

    void makeHomeNavItem();
    void makeHomeHNavItem();
    void makeHomeVNavItem();

    void makeDesignGuidanceNavItem();
    void makeDesignGuidanceHNavItem();
    void makeDesignGuidanceVNavItem();

    void makeSamplesNavItem();
    void makeSamplesHNavItem();
    void makeSamplesVNavItem();

    void makeBasicInputNavItem();
    void makeBasicInputHNavItem();
    void makeBasicInputVNavItem();

    void makeCollectionsNavItem();
    void makeCollectionsHNavItem();
    void makeCollectionsVNavItem();

    void makDateTimeNavItem();
    void makDateTimeHNavItem();
    void makDateTimeVNavItem();

    void makeDialogsFlyouts();
    void makeDialogsFlyoutsHNavItem();
    void makeDialogsFlyoutsVNavItem();

    void makeLayoutNavItem();
    void makeLayoutHNavItem();
    void makeLayoutVNavItem();

    void makeMediaNavItem();
    void makeMediaHNavItem();
    void makeMediaVNavItem();

    void makeSettingsNavItem();
    void makeSettingsHNavItem();
    void makeSettingsVNavItem();

    void makeMenuToolBarsNavItem();
    void makeMenuToolBarsHNavItem();
    void makeMenuToolBarsVNavItem();

    void makeNavigationNavItem();
    void makeNavigationHNavItem();
    void makeNavigationVNavItem();

    void makeScrollingNavItem();
    void makeScrollingHNavItem();
    void makeScrollingVNavItem();

    void makeStatusInfoNavItem();
    void makeStatusInfoHNavItem();
    void makeStatusInfoVNavItem();

    void makeTextNavItem();
    void makeTextHNavItem();
    void makeTextVNavItem();

    void resizeEvent(QResizeEvent *event);

    void closeEvent(QCloseEvent *event);

  public slots:
    void onClickedHCard(QString key);
    void onThemeChanged();

  protected:
    FluVNavigationView *m_vNavView;
    FluHNavigationView *m_hNavView;
    bool m_isHorizontalNav;
    FluStackedLayout *m_layout;
};
