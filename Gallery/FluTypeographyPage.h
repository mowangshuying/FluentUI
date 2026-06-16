#pragma once

#include "../Controls/FluWidget.h"
#include "FluAEmptyPage.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluLabel.h"
#include "../Controls/FluExpander.h"
#include "../Controls/FluCodeExpander.h"

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
