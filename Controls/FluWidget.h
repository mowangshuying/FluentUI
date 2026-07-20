#pragma once

#include <QWidget>
#include "../Utils/FluThemeUtils.h"

class FluWidget : public QWidget
{
    Q_OBJECT
  public:
    FluWidget(QWidget* parent = nullptr);

    virtual ~FluWidget()
    {
    }

    void paintEvent(QPaintEvent* event);
    void showEvent(QShowEvent* event);
  public slots:
    virtual void onThemeChanged()
    {
    }

  protected:
    FluTheme m_theme;
};
