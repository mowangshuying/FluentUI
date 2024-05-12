#pragma once

#include "FluWidget.h"
#include <QStyleOption>
#include <QPainter>
#include "../FluUtils/FluUtils.h"

class FluHSplitLine : public FluWidget
{
    Q_OBJECT
  public:
    FluHSplitLine(QWidget* parent = nullptr) : FluWidget(parent)
    {
        setFixedWidth(1);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHSplitLine.qss", this);
        // connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); }); { onThemeChanged(); });
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
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHSplitLine.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHSplitLine.qss", this);
        }
    }
};
