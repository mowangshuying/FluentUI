#pragma once

#include <QPushButton>
#include "../FluUtils/FluUtils.h"
#include <map>

class FluThemeButton : public QPushButton
{
    Q_OBJECT
  public:
    FluThemeButton(QWidget* parent = nullptr) : QPushButton(parent)
    {
        m_lightType = FluAwesomeType::Brightness;
        m_darkType = FluAwesomeType::QuietHours;
        m_grayType = FluAwesomeType::Light;

        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        setFixedSize(QSize(48, 32));
        setIconSize(QSize(16, 16));
        setMouseTracking(true);
        setAttribute(Qt::WA_Hover);

        connect(this, &FluThemeButton::clicked, this, [=]() {
            // if (FluThemeUtils::isDarkTheme())
            //{
            //     FluThemeUtils::getUtils()->setTheme(FluTheme::Light);
            // }

            if (FluThemeUtils::isLightTheme())
            {
                FluThemeUtils::getUtils()->setTheme(FluTheme::Dark);
            }
            else if (FluThemeUtils::isDarkTheme())
            {
                FluThemeUtils::getUtils()->setTheme(FluTheme::AtomOneDark);
            }
            else if (FluThemeUtils::isAtomOneDarkTheme())
            {
                FluThemeUtils::getUtils()->setTheme(FluTheme::Light);
            }

            onThemeChanged();

            emit clickedThemeButton();
        });

        onThemeChanged();
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

  signals:
    void clickedThemeButton();
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            setIcon(FluIconUtils::getFluentIcon(m_darkType, FluThemeUtils::getUtils()->getTheme()));
        }
        else if (FluThemeUtils::isDarkTheme())
        {
            setIcon(FluIconUtils::getFluentIcon(m_grayType, FluThemeUtils::getUtils()->getTheme()));
        }
        else if (FluThemeUtils::isAtomOneDarkTheme())
        {
            setIcon(FluIconUtils::getFluentIcon(m_lightType, FluThemeUtils::getUtils()->getTheme()));
        }

        FluStyleSheetUitls::setQssByFileName("FluThemeButton.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    FluAwesomeType m_darkType;
    FluAwesomeType m_lightType;
    FluAwesomeType m_grayType;
};
