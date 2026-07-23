#pragma once

#include <QWidget>
#include <QPainter>
#include "../Utils/FluThemeUtils.h"

class FluHNavigationIndicator : public QWidget
{
    Q_OBJECT
  public:
    FluHNavigationIndicator(QWidget *parent = nullptr);

    bool isSelected() const;
    void setSelected(bool b);

  protected:
    void paintEvent(QPaintEvent *event) override;

  private:
    bool m_selected;
};
