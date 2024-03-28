#pragma once

#include <QLabel>
#include "FluDef.h"
class FluStar : public QLabel
{
    Q_OBJECT
  public:
      FluStar(QWidget* parent = nullptr) : QLabel(parent)
      {
          //FluAwesomeType::FavoriteStar
          //FluAwesomeType::FavoriteStarFill
      }
};
