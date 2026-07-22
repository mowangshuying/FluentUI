#pragma once

#include <QWidget>
#include <QPainter>
#include "../Utils/FluThemeUtils.h"

class FluVNavigationIndicator : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool selected READ isSelected WRITE setSelected)
  public:
    FluVNavigationIndicator(QWidget *parent = nullptr);

    bool isSelected() const;
    void setSelected(bool b);

  protected:
    void paintEvent(QPaintEvent *event) override;

  private:
    bool m_selected;
};
