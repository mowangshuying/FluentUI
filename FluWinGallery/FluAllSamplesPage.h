#pragma once

#include "../FluControls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../FluControls/FluFWScrollView.h"
#include "../FluUtils/FluUtils.h"
#include "FluATitlePage.h"
#include "../FluControls/FluHCard.h"

class FluAllSamplesPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluAllSamplesPage(QWidget* parent = nullptr);

    void makeBasicInputCards();
    void makeCollectionsCards();
    void makeDateAndTimeCards();
    void makeDialogsAndFlyouts();

    void makeLayoutCards();
    void makeMediaCards();
    void makeMenusAndToolbars();
    void makeNavigationCards();
    void makeScrollingCards();
    void makeStatusInfoCards();
    void makeTextCards();
  signals:
    void clickedHCard(QString key);
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAllSamplesPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluAllSamplesPage.qss", this);
        }
    }

  protected:
    std::vector<FluHCard*> m_cards;
};
