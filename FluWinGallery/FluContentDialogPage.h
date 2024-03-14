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
            FluMessageBox messageBox("Save your work?", "***********  La La La! Ha! Ha! Ha! **********", window());
            messageBox.exec();
        });

        displayBox->getBodyLayout()->addWidget(showDlgBtn);

        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluContentDialogPage.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluContentDialogPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluContentDialogPage.qss", this);
        }
    }
};
