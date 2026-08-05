#pragma once

#include <QWidget>

#include "../utils/FluUtils.h"
#include "FluWidget.h"
#include <QEvent>
#include <QStyleOption>
#include <QPainter>

class FluDotInfoBadge : public FluWidget
{
    Q_OBJECT
  public:
    FluDotInfoBadge(QWidget* parent = nullptr);

    void setTopRightMargin(int marginTop, int marginRight);

    void moveTopRight();

    void paintEvent(QPaintEvent* event);

    bool eventFilter(QObject* watched, QEvent* event);

    static void setDotInfoBadge(QWidget* target, int marginTop, int marginRight);
    QString qssFileName() override
    {
        return "FluDotInfoBadge.qss";
    }

  protected:
    QWidget* m_target;

    int m_marginTop;
    int m_marginRight;
};
