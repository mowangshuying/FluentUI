#pragma once

#include "../FluUtils/FluUtils.h"
#include <QPushButton>

class FluStyleButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(bool pill READ getPill WRITE setPill)
  public:
    FluStyleButton(QWidget* parent = nullptr);

    void setPill(bool bPill)
    {
        m_bPill = bPill;
    }

    bool getPill()
    {
        return m_bPill;
    }

  public slots:
    void onThemeChanged();

  protected:
    bool m_bPill;
};
