#pragma once

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include "../FluUtils/FluUtils.h"

class FluVSplitLine : public QWidget
{
    Q_OBJECT
  public:
    FluVSplitLine(QWidget* parent = nullptr) : QWidget(parent)
    {
        setFixedHeight(1);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVSplitLine.qss", this);
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
};
