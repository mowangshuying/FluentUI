#include "FluHyperLinkButton.h"

FluHyperLinkButton::FluHyperLinkButton(QString linkUrl, QWidget* parent /* = nullptr*/) : QPushButton(parent), m_linkUrl(linkUrl)
{
    connect(this, &FluHyperLinkButton::clicked, [=](bool isClicked) { QDesktopServices::openUrl(QUrl(m_linkUrl)); });

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluHyperLinkButton::setLinkUrl(QString linkUrl)
{
    m_linkUrl = linkUrl;
}

void FluHyperLinkButton::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluHyperLinkButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}
