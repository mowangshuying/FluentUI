#pragma once

#include <QAction>
#include "FluDef.h"
#include "../FluUtils/FluUtils.h"

class FluAction : public QAction
{
    Q_OBJECT
  public:
    FluAction(QObject* parent = nullptr) : QAction(parent)
    {
        m_awesomeType = FluAwesomeType::None;
    }

    FluAction(QString text, QObject* parent = nullptr) : QAction(text, parent)
    {
        m_awesomeType = FluAwesomeType::None;
    }

    FluAction(QIcon icon, QString text, QObject* parent = nullptr) : QAction(icon, text, parent)
    {
        m_awesomeType = FluAwesomeType::None;
    }

    FluAction(FluAwesomeType type, QString text, QObject* parent = nullptr) : QAction(FluIconUtils::getFluentIcon(type, FluThemeUtils::getUtils()->getTheme()), text, parent)
    {
        m_awesomeType = type;
    }

    FluAwesomeType getAwesomeType()
    {
        return m_awesomeType;
    }

    void setAwesomeType(FluAwesomeType type)
    {
        m_awesomeType = type;
    }

  protected:
    FluAwesomeType m_awesomeType;
};
