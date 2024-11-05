#pragma once

#include "../FluControls/FluWidget.h"
#include "FluAEmptyPage.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluLabel.h"
#include "../FluControls/FluExpander.h"
#include "../FluControls/FluCodeExpander.h"

// a page to display label demo
class FluTypeographyPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluTypeographyPage(QWidget* parent = nullptr);

    QWidget* addARow(FluLabelStyle labelStyle, QString text1, QString text2, QString text3, QString text4, int nHeight);
  public slots:
    void onThemeChanged();

  protected:
    QLabel* m_imgLabel;
};
