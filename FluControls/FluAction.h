#pragma once

#include <QAction>
#include "FluDef.h"
#include "../FluUtils/FluUtils.h"
#include <QListWidgetItem>

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

    void setListWidgetItem(QListWidgetItem* item);

    QListWidgetItem* getListWidgetItem();
  public slots:
    void onThemeChanged();

  protected:
    QListWidgetItem* m_listWidgetItem;
    FluAwesomeType m_awesomeType;
};
