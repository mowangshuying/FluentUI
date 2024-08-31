#pragma once

#include <QAction>
#include "FluDef.h"
#include "../FluUtils/FluUtils.h"

class FluAction : public QAction
{
    Q_OBJECT
  public:
    FluAction(QObject* parent = nullptr);

    FluAction(QString text, QObject* parent = nullptr);

    FluAction(QIcon icon, QString text, QObject* parent = nullptr);

    FluAction(FluAwesomeType type, QString text, QObject* parent = nullptr);

    FluAwesomeType getAwesomeType();

    void setAwesomeType(FluAwesomeType type);

  protected:
    FluAwesomeType m_awesomeType;
};
