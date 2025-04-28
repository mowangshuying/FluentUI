#pragma once

#include <QPushButton>
#include <QStyle>

#include "../FluUtils/FluUtils.h"

class FluToggleButton : public QPushButton
{
    Q_OBJECT
  public:
    FluToggleButton(QWidget* parent = nullptr) : QPushButton(parent)
    {
        setFixedSize(120, 30);
        m_bToggled = false;
        setProperty("toggled", false);

        connect(this, &FluToggleButton::clicked, [=](bool bChecked) { onToggled(); });

        onThemeChanged();
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

    bool getToggled()
    {
        return m_bToggled;
    }

    void setToggled(bool bToggled)
    {
        m_bToggled = bToggled;
    }

  public slots:
    void onToggled()
    {
        m_bToggled = !m_bToggled;
        setProperty("toggled", m_bToggled);
        style()->polish(this);
        update();
    }

    void onThemeChanged()
    {
        FluStyleSheetUitls::setQssByFileName("FluToggleButton.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    bool m_bToggled;
};
