#pragma once

#include <QPushButton>
#include <QStyle>

#include "../utils/FluUtils.h"

class FluToggleButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(bool toggled READ getToggled WRITE setToggled NOTIFY toggledChanged)
  public:
    explicit FluToggleButton(QWidget* parent = nullptr);

    bool getToggled() const;

    void setToggled(bool isToggled);

  signals:
    void toggledChanged(bool isToggled);

  public slots:
    void onToggled();

    void onThemeChanged();

  protected:
    bool m_isToggled = false;
};