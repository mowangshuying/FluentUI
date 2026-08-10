#include "FluHyperLinkButton.h"

#include <QDesktopServices>
#include <QUrl>

FluHyperLinkButton::FluHyperLinkButton(const QString& linkUrl, QWidget* parent /* = nullptr*/) : QPushButton(parent), m_linkUrl(linkUrl)
{
    setAutoFillBackground(false);

    connect(this, &FluHyperLinkButton::clicked, this, [this]() {
        if (!m_linkUrl.isEmpty())
            QDesktopServices::openUrl(QUrl(m_linkUrl));
    });

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

const QString& FluHyperLinkButton::linkUrl() const
{
    return m_linkUrl;
}

void FluHyperLinkButton::setLinkUrl(const QString& linkUrl)
{
    m_linkUrl = linkUrl;
}

void FluHyperLinkButton::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluHyperLinkButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}
