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
    void setChecked(bool checked);

  public slots:
    void onThemeChanged();

  signals:
    void stateChanged(bool checked);

  protected:
    QString m_onText;
    QString m_offText;

    QHBoxLayout* m_mainLayout;
    FluToggleSwitchEx* m_toggleSwitchEx;
    FluLabel* m_textLabel;
};
