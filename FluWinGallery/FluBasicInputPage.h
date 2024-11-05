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
#include "../FluControls/FluCircleDot.h"

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
