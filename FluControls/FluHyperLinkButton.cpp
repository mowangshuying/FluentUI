#include "FluHyperLinkButton.h"

FluHyperLinkButton::FluHyperLinkButton(QString linkUrl, QWidget* parent /* = nullptr*/) : QPushButton(parent), m_linkUrl(linkUrl)
{
    connect(this, &FluHyperLinkButton::clicked, [=](bool bClicked) { QDesktopServices::openUrl(QUrl(m_linkUrl)); });
    // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHyperLinkButton.qss", this);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluHyperLinkButton::setLinkUrl(QString linkUrl)
{
    m_linkUrl = linkUrl;
}

void FluHyperLinkButton::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHyperLinkButton.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHyperLinkButton.qss", this);
    }
}
