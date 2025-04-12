#include "FluAppBarButtonPage.h"

FluAppBarButtonPage::FluAppBarButtonPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("AppBarButton"));
    m_infoLabel->setText(
        tr("App bar buttons differ from standard buttons in several ways:\n"
           "-Their default appearance is a transparent background with a smaller size\n"
           "-You use the Label and Icon properties to set the content instead of the content property.The Content property is ignored.\n"
           "-The button's IsCompact property control its size."));

    addSymbolIconAppBarButton();
    addKeyboardAcceleratorAppBarButton();

    onThemeChanged();
}

void FluAppBarButtonPage::addSymbolIconAppBarButton()
{
    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("An AppBarButton with a symbol icon."));
    displayBox->getCodeExpander()->setCodeByPath(FLURC("code/AppBarButtonPageCode1.md"));

    auto appBarButton = new FluAppBarButton(FluAwesomeType::Like);
    appBarButton->setText(tr("SymbolIcon"));
    displayBox->getBodyLayout()->addWidget(appBarButton);
    // connect(appBarButton, &FluAppBarButton::clicked, [=]() { LOG_DEBUG << "called"; });

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluAppBarButtonPage::addKeyboardAcceleratorAppBarButton()
{
    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("An AppBarButton with a KeyboardAccelerator."));
    displayBox->getCodeExpander()->setCodeByPath(FLURC("code/AppBarButtonPageCode2.md"));

    auto appBarButton = new FluAppBarButton(FluAwesomeType::Save);
    appBarButton->setText("Save");
    appBarButton->setShortCut(QKeySequence(Qt::CTRL + Qt::Key_S));
    displayBox->getBodyLayout()->addWidget(appBarButton);
    // connect(appBarButton, &FluAppBarButton::clicked, [=]() { LOG_DEBUG << "called"; });

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluAppBarButtonPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluAppBarButtonPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluAppBarButtonPage.qss"), this);
    }
}
