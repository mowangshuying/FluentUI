#pragma once

#include "FluATitlePage.h"
#include "../FluControls/FluHCard.h"
#include "../FluControls/FluFWScrollView.h"

class FluTextPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluTextPage(QWidget* parent = nullptr) : FluATitlePage(parent)
    {
        m_vMainLayout->setContentsMargins(35, 35, 0, 35);
        m_titleLabel->setText("Text");

        auto autoSuggestBoxCard = new FluHCard(QPixmap("../res/ControlImages/AutoSuggestBox.png"), "AutoSuggestBox", "A control to provide suggestions as a user is typing.");
        autoSuggestBoxCard->setKey("AutoSuggestBoxPage");
        getFWScrollView()->getMainLayout()->addWidget(autoSuggestBoxCard);
        connect(autoSuggestBoxCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        auto numberBoxCard = new FluHCard(QPixmap("../res/ControlImages/NumberBox.png"), "NumberBox", "A text control used for numeric input and evaluation of algebraic equations.");
        numberBoxCard->setKey("NumberBoxPage");
        getFWScrollView()->getMainLayout()->addWidget(numberBoxCard);
        connect(numberBoxCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        auto passwordBoxCard = new FluHCard(QPixmap("../res/ControlImages/PasswordBox.png"), "PasswordBox", "A control for entering passwords.");
        passwordBoxCard->setKey("PasswordBoxPage");
        getFWScrollView()->getMainLayout()->addWidget(passwordBoxCard);
        connect(passwordBoxCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        auto richEditBoxCard = new FluHCard(QPixmap("../res/ControlImages/RichEditBox.png"), "RichEditBox", "A rich text editing control that supports formatted text, hyperlinks and other rich content.");
        richEditBoxCard->setKey("RichEditBoxPage");
        getFWScrollView()->getMainLayout()->addWidget(richEditBoxCard);
        connect(richEditBoxCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        auto richTextBlockCard = new FluHCard(QPixmap("../res/ControlImages/RichTextBlock.png"), "RichTextBlock", "A control that displays formatted text hyperlinks, inline images, and other rich content.");
        richTextBlockCard->setKey("RichTextBlockPage");
        getFWScrollView()->getMainLayout()->addWidget(richTextBlockCard);
        connect(richTextBlockCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        auto textBlockCard = new FluHCard(QPixmap("../res/ControlImages/TextBlock.png"), "TextBlock", "A lightweight control for displaying small amounts of text.");
        textBlockCard->setKey("TextBlockPage");
        getFWScrollView()->getMainLayout()->addWidget(textBlockCard);
        connect(textBlockCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        auto textBoxCard = new FluHCard(QPixmap("../res/ControlImages/TextBox.png"), "TextBox", "A single-line or multi-line plain text field.");
        textBoxCard->setKey("TextBoxPage");
        getFWScrollView()->getMainLayout()->addWidget(textBoxCard);
        connect(textBoxCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTextPage.qss", this);
    }
  signals:
    void clickedHCard(QString key);
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTextPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTextPage.qss", this);
        }
    }
};
