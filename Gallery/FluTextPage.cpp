#include "FluTextPage.h"

FluTextPage::FluTextPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_vMainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText(tr("Text"));

    auto autoSuggestBoxCard = new FluHCard(FluIconUtils::getPixmap(("../res/ControlImages/AutoSuggestBox.png")), tr("AutoSuggestBox"), tr("A control to provide suggestions as a user is typing."));
    autoSuggestBoxCard->setKey("AutoSuggestBoxPage");
    getFWScrollView()->getMainLayout()->addWidget(autoSuggestBoxCard);
    connect(autoSuggestBoxCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto numberBoxCard = new FluHCard(FluIconUtils::getPixmap(("../res/ControlImages/NumberBox.png")), tr("NumberBox"), tr("A text control used for numeric input and evaluation of algebraic equations."));
    numberBoxCard->setKey("NumberBoxPage");
    getFWScrollView()->getMainLayout()->addWidget(numberBoxCard);
    connect(numberBoxCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto passwordBoxCard = new FluHCard(FluIconUtils::getPixmap(("../res/ControlImages/PasswordBox.png")), tr("PasswordBox"), tr("A control for entering passwords."));
    passwordBoxCard->setKey("PasswordBoxPage");
    getFWScrollView()->getMainLayout()->addWidget(passwordBoxCard);
    connect(passwordBoxCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto richEditBoxCard = new FluHCard(FluIconUtils::getPixmap(("../res/ControlImages/RichEditBox.png")), tr("RichEditBox"), tr("A rich text editing control that supports formatted text, hyperlinks and other rich content."));
    richEditBoxCard->setKey("RichEditBoxPage");
    getFWScrollView()->getMainLayout()->addWidget(richEditBoxCard);
    connect(richEditBoxCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto richTextBlockCard = new FluHCard(FluIconUtils::getPixmap(("../res/ControlImages/RichTextBlock.png")), tr("RichTextBlock"), tr("A control that displays formatted text hyperlinks, inline images, and other rich content."));
    richTextBlockCard->setKey("RichTextBlockPage");
    getFWScrollView()->getMainLayout()->addWidget(richTextBlockCard);
    connect(richTextBlockCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto textBlockCard = new FluHCard(FluIconUtils::getPixmap(("../res/ControlImages/TextBlock.png")), tr("TextBlock"), tr("A lightweight control for displaying small amounts of text."));
    textBlockCard->setKey("TextBlockPage");
    getFWScrollView()->getMainLayout()->addWidget(textBlockCard);
    connect(textBlockCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto textBoxCard = new FluHCard(FluIconUtils::getPixmap(("../res/ControlImages/TextBox.png")), tr("TextBox"), tr("A single-line or multi-line plain text field."));
    textBoxCard->setKey("TextBoxPage");
    getFWScrollView()->getMainLayout()->addWidget(textBoxCard);
    connect(textBoxCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    onThemeChanged();
}

void FluTextPage::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluTextPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
