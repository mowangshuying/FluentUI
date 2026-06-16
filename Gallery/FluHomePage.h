#pragma once

#include "../Controls/FluWidget.h"

#include "../Utils/FluStyleSheetUitls.h"
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include "FluHomePageTitle.h"
#include "../Controls/FluFlowLayout.h"
#include "../Controls/FluHCard.h"
#include "../Controls/FluVScrollView.h"

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
