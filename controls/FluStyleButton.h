#pragma once

#include "../Utils/FluUtils.h"
#include <QPushButton>

class FluStyleButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(bool pill READ getPill WRITE setPill)
  public:
    FluStyleButton(QWidget* parent = nullptr);

    void setPill(bool isPill)
    {
        m_isPill = isPill;
    }

    bool getPill()
    {
        return m_isPill;
    }

  public slots:
    void onThemeChanged();

  protected:
    bool m_isPill;
};
