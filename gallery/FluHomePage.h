#pragma once

#include "../controls/FluWidget.h"

#include "../utils/FluStyleSheetUtils.h"
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include "FluHomePageTitle.h"
#include "../controls/FluFlowLayout.h"
#include "../controls/FluHCard.h"
#include "../controls/FluVScrollView.h"

class FluHomePage : public FluVScrollView
{
    Q_OBJECT
  public:
    FluHomePage(QWidget *parent = nullptr);

  public slots:
    void onThemeChanged();
  signals:
    void clickedHCard(QString key);

  protected:
};
