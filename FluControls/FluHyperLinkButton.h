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

    protected:
      QString m_linkUrl;
};
