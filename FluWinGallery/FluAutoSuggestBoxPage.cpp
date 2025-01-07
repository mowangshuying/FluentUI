#include "FluAutoSuggestBoxPage.h"

FluAutoSuggestBoxPage::FluAutoSuggestBoxPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("AutoSuggestBox"));
    m_infoLabel->setText(tr("A text control that makes suggestions to users as they type. The app is notified when text has been changed by user and is responsible for providing relevant suggestions for this control to display."));

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("A basic autosuggest box."));
    displayBox->getCodeExpander()->setCodeByPath("../code/AutoSuggestBoxPageCode1.md");

    auto autoSuggestBox = new FluAutoSuggestBox;
    autoSuggestBox->setFixedWidth(300);
    autoSuggestBox->setKeys({tr("a"), tr("ab"), tr("abc"), tr("abcd"), tr("abcde")});
    displayBox->getBodyLayout()->addWidget(autoSuggestBox);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAutoSuggestBoxPage.qss", this);
}

void FluAutoSuggestBoxPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAutoSuggestBoxPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluAutoSuggestBoxPage.qss", this);
    }
}
