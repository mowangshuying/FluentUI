#pragma once

#include "../controls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "FluATitlePage.h"
#include "../controls/FluFWScrollView.h"
#include "../utils/FluUtils.h"
#include "../controls/FluHCard.h"

class FluDateAndTimePage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluDateAndTimePage(QWidget* parent = nullptr);


  public slots:
    void onThemeChanged();
};
