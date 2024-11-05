#pragma once

#include "../FluControls/FluFrameLessWidget.h"
#include "../FluControls/FluVNavigationView.h"
#include "../FluControls/FluVNavigationIconTextItem.h"
#include "FluHomePage.h"
#include <QStackedLayout>
#include "../FluControls/FluStackedLayout.h"
#include "FluTypeographyPage.h"
#include "../FluControls/FluVNavigationSettingsItem.h"
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
#include <QPainter>
#include <QStyleOption>
#include "FluMenuBarPage.h"
#include "FluNumberBoxPage.h"
#include "FluInfoBadgePage.h"
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

class FluGalleryWindow : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    FluGalleryWindow(QWidget *parent = nullptr);

    void makeHomeNavItem();

    void makeDesignGuidanceNavItem();

    void makeSamplesNavItem();

    void makeBasicInputNavItem();

    void makeCollectionsNavItem();

    void makDateTimeNavItem();

    void makeDialogsFlyouts();

    void makeLayoutNavItem();

    void makeMediaNavItem();

    void makeSettingsNavItem();

    void makeMenuToolBarsNavItem();

    void makeNavigationNavItem();

    void makeScrollingNavItem();

    void makeStatusInfoNavItem();

    void makeTextNavItem();

    void resizeEvent(QResizeEvent *event);

    void closeEvent(QCloseEvent *event);

  public slots:
    void onThemeChanged();

  protected:
    FluVNavigationView *m_navView;
    FluStackedLayout *m_sLayout;
};
