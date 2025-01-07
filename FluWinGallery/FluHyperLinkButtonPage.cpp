#include "FluHyperLinkButtonPage.h"

FluHyperLinkButtonPage::FluHyperLinkButtonPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("HyperLinkButton"));
    // m_subTitleLabel->setText("FluentUI::FluHyperLinkButton");
    m_infoLabel->setText(tr("A HyperlinkButton appears as a text hyperlink. When a user clicks it, it opens the page you specify in the uri property in the default browser.Or your can handle its Click event, typically to navigate within your app."));

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("A hyperlink button with a Url."));
    displayBox1->getCodeExpander()->setCodeByPath("../code/HyperLinkButtonPageCode1.md");

    auto btn1 = new FluHyperLinkButton("https://github.com/mowangshuying/FluentUI");
    btn1->setText(tr("FluentUI Repo Url"));
    btn1->setFixedWidth(200);

    displayBox1->setBodyWidgetFixedHeight(66);
    displayBox1->getBodyLayout()->addWidget(btn1);
    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    onThemeChanged();
}

void FluHyperLinkButtonPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHyperLinkButtonPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHyperLinkButtonPage.qss", this);
    }
}
