#pragma once

#include <QWidget>
#include "../FluUtils/FluThemeUtils.h"

class FluWidget : public QWidget
{
    Q_OBJECT
  public:
    FluWidget(QWidget* parent = nullptr);

    void showEvent(QShowEvent* event);
  public slots:
    virtual void onThemeChanged()
    {
    }
  protected:
    FluTheme m_theme;
};
