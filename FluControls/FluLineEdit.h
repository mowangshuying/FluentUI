#pragma once

#include <QLineEdit>
#include "FluDef.h"
#include "../FluUtils/FluUtils.h"
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>

class FluLineEdit : public QLineEdit
{
    Q_OBJECT
  public:
    FluLineEdit(QWidget* parent = nullptr) : QLineEdit(parent)
    {
        //  setContentsMargins(4, 4, 4, 4);
        onThemeChanged();
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

    void paintEvent(QPaintEvent* event)
    {
        QLineEdit::paintEvent(event);
        QPainter painter(this);
        painter.setPen(Qt::NoPen);
        painter.setRenderHints(QPainter::Antialiasing);
        if (!hasFocus())
            return;

        FluStyleSheetUitls::drawBottomLineIndicator(this, &painter);
    }
  public slots:
    virtual void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluLineEdit.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluLineEdit.qss", this);
        }
    }
};
