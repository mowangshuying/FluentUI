#pragma once

#include "../FluControls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "FluATitlePage.h"
#include "../FluControls/FluFWScrollView.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluHCard.h"

class FluDateAndTimePage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluDateAndTimePage(QWidget* parent = nullptr);

  signals:
    void clickedHCard(QString key);
  public slots:
    void onThemeChanged();
};
