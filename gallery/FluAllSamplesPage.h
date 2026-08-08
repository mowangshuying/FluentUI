#pragma once

#include "../controls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../controls/FluFWScrollView.h"
#include "../utils/FluUtils.h"
#include "FluATitlePage.h"
#include "../controls/FluHCard.h"

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
    void makeNavigationCards();
    void makeScrollingCards();
    void makeStatusInfoCards();
    void makeTextCards();

  public slots:
    void onThemeChanged();
};
