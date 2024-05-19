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

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluToggleButton.qss", this);
        connect(this, &FluToggleButton::clicked, [=](bool bChecked) {
            m_bToggled = !m_bToggled;
            setProperty("toggled", m_bToggled);
            style()->polish(this);
            update();
        });

        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluToggleButton.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluToggleButton.qss", this);
        }
    }

  protected:
    bool m_bToggled;
};
