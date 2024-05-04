#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluAppBarButton.h"

class FluAppBarButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
      FluAppBarButtonPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
      {
          m_mainLayout->setAlignment(Qt::AlignTop);
          m_titleLabel->setText("AppBarButton");
          m_infoLabel->setText(
              "App bar buttons differ from standard buttons in several ways:\n"
              "-Their default appearance is a transparent background with a smaller size\n"
              "-You use the Label and Icon properties to set the content instead of the content property.The Content property is ignored.\n"
              "-The button's IsCompact property control its size.");

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAppBarButtonPage.qss", this);

        auto displayBox1 = new FluDisplayBox;
        displayBox1->setTitle("An AppBarButton with a symbol icon.");
        displayBox1->getCodeExpander()->setCodeByPath("../code/AppBarButtonPageCode1.md");

        auto appBarButton = new FluAppBarButton(FluAwesomeType::Like);
        appBarButton->setText("SymbolIcon");
        displayBox1->getBodyLayout()->addWidget(appBarButton);

        m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });

      }

      public slots:
      void onThemeChanged()
      {
          if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAppBarButtonPage.qss", this);
          }
          else
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluAppBarButtonPage.qss", this);
          }
      }

};
