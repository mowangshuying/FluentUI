#pragma once

#include "FluAEmptyPage.h"

#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluAutoSuggestBox.h"

class FluAutoSuggestBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluAutoSuggestBoxPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("AutoSuggestBox");
        m_infoLabel->setText("A text control that makes suggestions to users as they type. The app is notified when text has been changed by user and is responsible for providing relevant suggestions for this control to display.");

        auto displayBox = new FluDisplayBox;
        displayBox->setTitle("A basic autosuggest box.");
        displayBox->getCodeExpander()->setCodeByPath("../code/AutoSuggestBoxPageCode1.md");

        auto autoSuggestBox = new FluAutoSuggestBox;
        autoSuggestBox->setFixedWidth(300);
        autoSuggestBox->setKeys({"a", "ab", "abc", "abcd", "abcde"});
        displayBox->getBodyLayout()->addWidget(autoSuggestBox);

        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAutoSuggestBoxPage.qss", this);
    }
  public slots:
    void onThemeChanged()
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
};
