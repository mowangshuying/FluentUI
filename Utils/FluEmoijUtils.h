#pragma once

#include <QPixmap>
#include <QString>
#include "../Controls/FluDef.h"
class FluEmoijUtils
{
  private:
    FluEmoijUtils();
    ~FluEmoijUtils();

  public:
    static QPixmap getSvgPixmap(QString svgPath);
    static QPixmap getSvgPixmap(FluEmoijType type);
    static QIcon getSvgIcon(QString svgPath);
    static QIcon getSvgIcon(FluEmoijType type);
};
