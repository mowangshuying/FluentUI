#pragma once

#include <QWidget>

#include "../Utils/FluUtils.h"
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
    QString qssFileName() override
    {
        return "FluCircleDot.qss";
    }

  protected:
    QWidget* m_target;

    int m_nMarginTop;
    int m_nMarginRight;
};
