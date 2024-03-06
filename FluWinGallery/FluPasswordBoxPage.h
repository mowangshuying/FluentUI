#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluPasswordBox.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluPasswordBoxPage : public FluAEmptyPage
{
	Q_OBJECT
  public:
	  FluPasswordBoxPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
	  {
              m_mainLayout->setAlignment(Qt::AlignTop);
              m_titleLabel->setText("PasswordBox");
              m_infoLabel->setText("A user can enter a single line of non-wrapping text in a PasswordBox control. The text is Masked by characters that you can specify by using the PasswordChar property, and you can specify the maximum number of characters that the user can enter by setting the MaxLength property.");
			
			    auto displayBox1 = new FluDisplayBox;
              displayBox1->setTitle("A simple PasswordBox.");
              displayBox1->getCodeExpander()->setCodeByPath("../code/PasswordBoxPageCode1");

              auto passwordBox = new FluPasswordBox(this);
              passwordBox->setFixedWidth(240);
              displayBox1->setBodyWidgetFixedHeight(96);
              displayBox1->getBodyLayout()->addWidget(passwordBox);
              m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);
	  }
};
