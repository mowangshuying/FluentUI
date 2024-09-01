#pragma once

#include <QWidget>

#include "../FluUtils/FluUtils.h"
#include "FluWidget.h"
#include <QEvent>
#include <QStyleOption>
#include <QPainter>

class FluCircleDot : public FluWidget
{
    Q_OBJECT
  public:
    FluCircleDot(QWidget* parent = nullptr);

    void setTopRightMargin(int nMarginTop, int nMarginRight);

    void moveTopRight();

    void paintEvent(QPaintEvent* event);

    bool eventFilter(QObject* watched, QEvent* event);

    static void setCircleDot(QWidget* target, int nMarginTop, int nMarginRight);
  public slots:

    void onThemeChanged();

  protected:
    QWidget* m_target;

    int m_nMarginTop;
    int m_nMarginRight;
};
