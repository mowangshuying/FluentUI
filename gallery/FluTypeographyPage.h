#pragma once

#include "../controls/FluWidget.h"
#include "FluAEmptyPage.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluLabel.h"
#include "../controls/FluExpander.h"
#include "../controls/FluCodeExpander.h"

// a page to display label demo
class FluTypeographyPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluTypeographyPage(QWidget* parent = nullptr);

    QWidget* addARow(FluLabelStyle labelStyle, QString text1, QString text2, QString text3, QString text4, int height);
  public slots:
    void onThemeChanged();

  protected:
    QLabel* m_imgLabel;
};
