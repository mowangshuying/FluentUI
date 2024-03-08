#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluMessageBox.h"

class FluContentDialogPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluContentDialogPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("ContentDialog");
        m_infoLabel->setText("Use a ContentDialog to show relavant information to provide a modal dialog experience that can show any text content.");

        auto displayBox = new FluDisplayBox;
        displayBox->setTitle("A basic content dialog with content.");
        displayBox->getCodeExpander()->setCodeByPath("../code/ContentDialogPageCode1");
        displayBox->setBodyWidgetFixedHeight(56);

        auto showDlgBtn = new FluPushButton;
        showDlgBtn->setText("Show dialog");
        showDlgBtn->setFixedSize(100, 30);

        connect(showDlgBtn, &FluPushButton::clicked, [=]() {
            FluMessageBox messageBox("Save your work?", "--\--\--\/--/--/--", window());
            messageBox.exec();
        });

        displayBox->getBodyLayout()->addWidget(showDlgBtn);

        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluContentDialogPage.qss", this);

    }
};
