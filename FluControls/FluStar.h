#pragma once

#include <QLabel>
#include "FluDef.h"
#include "../FluUtils/FluUtils.h"

class FluStar : public QLabel
{
    Q_OBJECT
  public:
    FluStar(QWidget* parent = nullptr) : QLabel(parent)
    {
        //     if (testAttribute(Qt::WA_Hover))
        //         LOG_DEBUG << "has hover attr.";
        //     else
        //         LOG_DEBUG << "not has hover attr.";

        setAttribute(Qt::WA_Hover);
        setFixedSize(25, 25);
        setEmptyStar();
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged,  this, [=](FluTheme theme) { onThemeChanged(); });
    }

    void setEmptyStar()
    {
        m_bSolid = false;
        setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::FavoriteStar, FluThemeUtils::getUtils()->getTheme()));
    }

    void setSolidStar()
    {
        m_bSolid = true;
        setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::FavoriteStarFill, QColor(0, 90, 158)));
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Dark)
        {
            setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::FavoriteStarFill, QColor(118, 185, 237)));
        }
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            if (m_bSolid)
            {
                setSolidStar();
            }
            else
            {
                setEmptyStar();
            }
        }
        else
        {
            if (m_bSolid)
            {
                setSolidStar();
            }
            else
            {
                setEmptyStar();
            }
        }
    }

  protected:
    bool m_bSolid;
};
