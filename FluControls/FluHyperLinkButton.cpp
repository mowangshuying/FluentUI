#include "FluHyperLinkButton.h"

FluHyperLinkButton::FluHyperLinkButton(QString linkUrl, QWidget* parent /* = nullptr*/) : QPushButton(parent), m_linkUrl(linkUrl)
{
    connect(this, &FluHyperLinkButton::clicked, [=](bool bClicked) { QDesktopServices::openUrl(QUrl(m_linkUrl)); });
    FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluHyperLinkButton.qss", this);
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}
