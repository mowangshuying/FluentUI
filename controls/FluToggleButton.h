#pragma once

#include <QPushButton>
#include <QStyle>

#include "../Utils/FluUtils.h"

class FluToggleButton : public QPushButton
{
    Q_OBJECT
  public:
    FluToggleButton(QWidget* parent = nullptr) : QPushButton(parent)
    {
        setFixedSize(120, 30);
        m_isToggled = false;
        setProperty("toggled", false);

        connect(this, &FluToggleButton::clicked, [=](bool isChecked) { onToggled(); });

        onThemeChanged();
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

    bool getToggled()
    {
        return m_isToggled;
    }

    void setToggled(bool isToggled)
    {
        m_isToggled = isToggled;
    }

  public slots:
    void onToggled()
    {
        m_isToggled = !m_isToggled;
        setProperty("toggled", m_isToggled);
        style()->polish(this);
        update();
    }

    void onThemeChanged()
    {
        FluStyleSheetUtils::setQssByFileName("FluToggleButton.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    bool m_isToggled;
};
