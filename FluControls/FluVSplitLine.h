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
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVSplitLine.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluVSplitLine.qss", this);
        }
    }
};
