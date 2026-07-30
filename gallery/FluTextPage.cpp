#include "FluTextPage.h"

FluTextPage::FluTextPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_mainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText(tr("Text"));

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/AutoSuggestBox.png")), tr("AutoSuggestBox"), tr("A control to provide suggestions as a user is typing."), "AutoSuggestBoxPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/NumberBox.png")), tr("NumberBox"), tr("A text control used for numeric input and evaluation of algebraic equations."), "NumberBoxPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/PasswordBox.png")), tr("PasswordBox"), tr("A control for entering passwords."), "PasswordBoxPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/RichEditBox.png")), tr("RichEditBox"), tr("A rich text editing control that supports formatted text, hyperlinks and other rich content."), "RichEditBoxPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/RichTextBlock.png")), tr("RichTextBlock"), tr("A control that displays formatted text hyperlinks, inline images, and other rich content."), "RichTextBlockPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/TextBlock.png")), tr("TextBlock"), tr("A lightweight control for displaying small amounts of text."), "TextBlockPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/TextBox.png")), tr("TextBox"), tr("A single-line or multi-line plain text field."), "TextBoxPage");

    onThemeChanged();
}

void FluTextPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluTextPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
