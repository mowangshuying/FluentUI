#pragma once

#include "FluToggleSwitchEx.h"
#include "FluLabel.h"

#include <QHBoxLayout>

class FluTextToggleSwitchEx : public FluWidget
{
    Q_OBJECT
  public:
    FluTextToggleSwitchEx(QWidget* parent = nullptr);

    void setText(QString onText, QString offText);
  public slots:
    void onThemeChanged();

  protected:
    QString m_onText;
    QString m_offText;

    QHBoxLayout* m_hMainLayout;
    FluToggleSwitchEx* m_toggleSwithEx;
    FluLabel* m_textLabel;
};
