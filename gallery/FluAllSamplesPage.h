#pragma once

#include "../Controls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../Controls/FluFWScrollView.h"
#include "../Utils/FluUtils.h"
#include "FluATitlePage.h"
#include "../Controls/FluHCard.h"

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
    void onThemeChanged();

  protected:
    std::vector<FluHCard*> m_cards;
};
