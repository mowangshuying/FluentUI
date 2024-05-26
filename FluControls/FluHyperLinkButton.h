#pragma once

#include <QPushButton>
#include "../FluUtils/FluUtils.h"
#include <QDesktopServices>

class FluHyperLinkButton : public QPushButton
{
    Q_OBJECT
  public:
    FluHyperLinkButton(QString linkUrl, QWidget* parent = nullptr);

    void setLinkUrl(QString linkUrl)
    {
        m_linkUrl = linkUrl;
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluHyperLinkButton.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/dark/FluHyperLinkButton.qss", this);
        }
    }

  protected:
    QString m_linkUrl;
};
