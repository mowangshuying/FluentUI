#pragma once

#include <QPushButton>
#include "../Utils/FluUtils.h"
#include <QDesktopServices>

class FluHyperLinkButton : public QPushButton
{
    Q_OBJECT
  public:
    FluHyperLinkButton(QString linkUrl, QWidget* parent = nullptr);

    void setLinkUrl(QString linkUrl);

  public slots:
    void onThemeChanged();

  protected:
    QString m_linkUrl;
};
