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
        setFixedSize(25, 25);
        setEmptyStar();
    }

    void setEmptyStar()
    {
        setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::FavoriteStar, FluThemeUtils::getUtils()->getTheme()));
    }

    void setSolidStar()
    {
        setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::FavoriteStarFill, QColor(0, 90, 158)));
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Dark)
        {
            setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::FavoriteStarFill, QColor(118, 185, 237)));
        }
    }
};
