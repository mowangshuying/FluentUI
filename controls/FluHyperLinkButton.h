#pragma once

#include <QPushButton>
#include "../utils/FluUtils.h"

class FluHyperLinkButton : public QPushButton
{
    Q_OBJECT
  public:
    explicit FluHyperLinkButton(const QString& linkUrl, QWidget* parent = nullptr);

    const QString& linkUrl() const;

    void setLinkUrl(const QString& linkUrl);

  protected:
    void onThemeChanged();

  private:
    QString m_linkUrl;
};
