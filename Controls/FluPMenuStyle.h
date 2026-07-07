#pragma once

// #include <QStyle>
#include <QProxyStyle>

class FluPMenuStyle : public QProxyStyle
{
    Q_OBJECT
public:
    FluPMenuStyle(QStyle* baseStyle = nullptr) : QProxyStyle(baseStyle)
    {
    }

    void drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption* option = nullptr, const QWidget* widget = nullptr) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const override;

protected:
    int m_nMenuItemHeight = 30;
};