#pragma once

#include <QWidget>
#include <QPainter>
#include <QPropertyAnimation>
#include "../Utils/FluThemeUtils.h"

class FluHNavigationIndicator : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int indicatorWidth READ indicatorWidth WRITE setIndicatorWidth)
  public:
    FluHNavigationIndicator(QWidget *parent = nullptr);

    bool isSelected() const;
    void setSelected(bool b);

    int indicatorWidth() const;
    void setIndicatorWidth(int w);

    void animateSelect(bool selected);

  protected:
    void paintEvent(QPaintEvent *event) override;

  private:
    bool m_selected;
    int m_indicatorWidth;
    QPropertyAnimation *m_widthAnimation;
};
