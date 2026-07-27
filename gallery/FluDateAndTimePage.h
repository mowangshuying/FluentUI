#pragma once

#include "../Controls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "FluATitlePage.h"
#include "../Controls/FluFWScrollView.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluHCard.h"

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
