#pragma once

#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>

#include "../FluUtils/FluUtils.h"

class FluPushButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(bool pill READ getPill WRITE setPill)
  public:
    FluPushButton(QWidget *parent = nullptr);

    FluPushButton(const QString &text, QWidget *parent = nullptr);

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