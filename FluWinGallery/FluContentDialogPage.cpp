#include "FluContentDialogPage.h"

FluContentDialogPage::FluContentDialogPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("ContentDialog"));
    m_infoLabel->setText(tr("Use a ContentDialog to show relavant information to provide a modal dialog experience that can show any text content."));

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("A basic content dialog with content."));
    displayBox->getCodeExpander()->setCodeByPath(FLURC("code/ContentDialogPageCode1.md"));
    displayBox->setBodyWidgetFixedHeight(56);

    auto showDlgBtn = new FluPushButton;
    showDlgBtn->setText(tr("Show dialog"));
    showDlgBtn->setFixedSize(100, 30);

    connect(showDlgBtn, &FluPushButton::clicked, [=]() {
        FluMessageBox messageBox(tr("Save your work?"), tr("This just a message box."), window());
        messageBox.exec();
    });

    displayBox->getBodyLayout()->addWidget(showDlgBtn);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    onThemeChanged();
}

void FluContentDialogPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluContentDialogPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluContentDialogPage.qss"), this);
    }
}
