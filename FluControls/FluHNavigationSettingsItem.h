#pragma once

#include "FluHNavigationItem.h"
#include <QHBoxLayout>
#include "FluRotationButton.h"
#include <QPainter>
#include <QStyleOption>

class FluHNavigationSettingsItem : public FluHNavigationItem
{
    Q_OBJECT
  public:
    FluHNavigationSettingsItem(QWidget* parent = nullptr);

    FluHNavigationSettingsItem(FluAwesomeType awesomeType, QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    FluAwesomeType m_awesomeType;
    FluRotationButton* m_icon;
    QHBoxLayout* m_hMainLayout;
};
