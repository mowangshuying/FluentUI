#pragma once

#include "FluWidget.h"
#include <QVBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "FluLabel.h"
#include "FluPushButton.h"
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>

enum class FluFlyoutPosition
{
    Top,
    Bottom,
    Left,
    Right,
};

class FluVFlyout : public FluWidget
{
    Q_OBJECT
  public:
    FluVFlyout(QWidget* target, FluFlyoutPosition position = FluFlyoutPosition::Top);

    // void resizeEvent(QResizeEvent* event)
    //  {
    //      m_shadowWidget->resize(width(), height());
    //   }

    void showEvent(QShowEvent* event);

    void closeEvent(QCloseEvent* event);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    QHBoxLayout* m_hMainLayout;
    QWidget* m_shadowWidget;
    QGraphicsDropShadowEffect* m_shadowEffect;

    QVBoxLayout* m_vShadowLayout;
    QWidget* m_targetWidget;
    FluFlyoutPosition m_position;
};
