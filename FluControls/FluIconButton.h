#pragma once

#include <QPushButton>
#include "FluDef.h"
#include "../FluUtils/FluUtils.h"
// to display fluent icon use fluent font 
class FluIconButton : public QPushButton
{
    Q_OBJECT
  public:
    FluIconButton(QWidget* parent = nullptr) : QPushButton(parent)
    {   
        //set fixed size 
        setFixedSize(30, 30);
        setIconSize(QSize(20, 20));

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluIconButton.qss", this);
    }

    FluIconButton(FluAwesomeType type1, QWidget* parent = nullptr)
        : QPushButton(parent)
    {
        setFixedSize(30, 30);
        setIconSize(QSize(20, 20));
        // please ensure type1 will in FluAwesomeType, if can't suitable may crash.
        
        QPixmap  pixmap = FluIconUtils::getFluentIconPixmap(type1);
        pixmap = pixmap.scaled(20, 20);
        setIcon(QIcon(pixmap));

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluIconButton.qss", this);
    }

  protected:
    FluAwesomeType m_type1;
    FluAwesomeType m_type2;
};
