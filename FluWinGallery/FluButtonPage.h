#pragma once

#include <QFrame>

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluPushButton.h"

class FluButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
      FluButtonPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
      {
          m_mainLayout->setAlignment(Qt::AlignTop);
          m_titleLabel->setText("ButtonPage");
          m_infoLabel->setText("Display Buttons.");
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluButtonPage.qss", this);

          auto displayBox1 = new FluDisplayBox;
        //  displayBox1->setFixedHeight(140);
          displayBox1->setTitle("A simple button with text content.");
           auto btn1 = new FluPushButton(this);
           btn1->setText("Standard XAML button");
           displayBox1->setBodyWidgetFixedHeight(96);
           displayBox1->getBodyLayout()->addWidget(btn1);
         // addDemo(btn1);

          m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);
          //m_mainLayout->addStretch();
      }
};
