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
#include "../Controls/FluCircleDot.h"

class FluBasicInputPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluBasicInputPage(QWidget* parent = nullptr);

  signals:
    void clickedHCard(QString key);
  public slots:
    void onThemeChanged();

  protected:
};
