#pragma once

#include <QWidget>
#include <QPainter>
#include <QPropertyAnimation>
#include "../Utils/FluThemeUtils.h"

class FluVNavigationIndicator : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int indicatorHeight READ indicatorHeight WRITE setIndicatorHeight)
  public:
    FluVNavigationIndicator(QWidget *parent = nullptr);

    bool isSelected() const;
    void setSelected(bool b);

    int indicatorHeight() const;
    void setIndicatorHeight(int h);

  protected:
    void paintEvent(QPaintEvent *event) override;

  private:
    bool m_selected;
    int m_indicatorHeight;
    int m_targetHeight;
    QPropertyAnimation *m_heightAnimation;
};