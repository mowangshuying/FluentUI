#pragma once

#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>

#include "../Utils/FluUtils.h"

class FluPushButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(bool pill READ getPill WRITE setPill)
  public:
    FluPushButton(QWidget *parent = nullptr);

    FluPushButton(const QString &text, QWidget *parent = nullptr);

    void setPill(bool isPill)
    {
        m_isPill = isPill;
    }

    bool getPill()
    {
        return m_isPill;
    }
  protected:
    void onThemeChanged();
    bool m_isPill;
};