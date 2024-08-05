#pragma once

#include "../FluControls/FluWidget.h"

#include "../FluUtils/FluStyleSheetUitls.h"
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include "FluHomePageTitle.h"
#include "../FluControls/FluFlowLayout.h"
#include "../FluControls/FluHCard.h"
#include "../FluControls/FluVScrollView.h"

class FluHomePage : public FluVScrollView
{
    Q_OBJECT
  public:
    FluHomePage(QWidget *parent = nullptr);

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHomePage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHomePage.qss", this);
        }
    }
  signals:
    void clickedHCard(QString key);

  protected:
};
