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
#include "../controls/FluCircleDot.h"

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
