#pragma once

#include <QPushButton>
#include "../FluUtils/FluUtils.h"
#include <QStyle>

class FluPivotTitleBarItem : public QPushButton
{
    Q_OBJECT
  public:
    FluPivotTitleBarItem(QWidget* parent = nullptr) : QPushButton(parent)
    {
        setSelected(false);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPivotTitleBarItem.qss", this);
        
    }

    void setSelected(bool bSelected)
    {
        setProperty("selected", bSelected);
        style()->polish(this);
    }

    void setKey(QString key)
    {
        m_key = key;
        setText(key);
    }

    QString getKey()
    {
        return m_key;
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPivotTitleBarItem.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluPivotTitleBarItem.qss", this);
        }
    }

  protected:
    QString m_key;
};
