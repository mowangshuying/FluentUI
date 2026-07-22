#pragma once

// #include <QStyle>
#include <QProxyStyle>

class FluPMenuStyle : public QProxyStyle
{
    Q_OBJECT
  public:
    FluPMenuStyle(QStyle* baseStyle = nullptr);

    QColor getMenuBackgroundColor() const
    {
        return m_menuBackgroundColor;
    }

    void setMenuBackgroundColor(const QColor& color)
    {
        m_menuBackgroundColor = color;
    }

    QColor getMenuBorderColor() const
    {
        return m_menuBorderColor;
    }

    void setMenuBorderColor(const QColor& color)
    {
        m_menuBorderColor = color;
    }

    QColor getMenuItemNormalBackgroundColor() const
    {
        return m_menuItemNormalBackgroundColor;
    }

    void setMenuItemNormalBackgroundColor(const QColor& color)
    {
        m_menuItemNormalBackgroundColor = color;
    }

    QColor getMenuItemSelectedBackgroundColor() const
    {
        return m_menuItemSelectedBackgroundColor;
    }

    void setMenuItemSelectedBackgroundColor(const QColor& color)
    {
        m_menuItemSelectedBackgroundColor = color;
    }

    QColor getMenuItemDisabledBackgroundColor() const
    {
        return m_menuItemDisabledBackgroundColor;
    }

    void setMenuItemDisabledBackgroundColor(const QColor& color)
    {
        m_menuItemDisabledBackgroundColor = color;
    }

    QColor getMenuItemForegroundColor() const
    {
        return m_menuItemForegroundColor;
    }

    void setMenuItemForegroundColor(const QColor& color)
    {
        m_menuItemForegroundColor = color;
    }

    int getMenuItemSpacing() const
    {
        return m_nMenuItemSpacing;
    }

    void setMenuItemSpacing(int spacing)
    {
        m_nMenuItemSpacing = spacing;
    }

    int getMenuItemIconWH() const
    {
        return m_nMenuItemIconWH;
    }

    void setMenuItemIconWH(int iconWH)
    {
        m_nMenuItemIconWH = iconWH;
    }

    int getMenuItemHeight() const
    {
        return m_nMenuItemHeight;
    }

    void setMenuItemHeight(int height)
    {
        m_nMenuItemHeight = height;
    }

    void drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption* option = nullptr, const QWidget* widget = nullptr) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const override;

  protected:
    QColor m_menuBackgroundColor = QColor(243, 243, 243);
    QColor m_menuBorderColor = QColor(200, 200, 200);

    // menu item;
    QColor m_menuItemNormalBackgroundColor = QColor(243, 243, 243);
    QColor m_menuItemSelectedBackgroundColor = QColor(220, 220, 220);
    QColor m_menuItemDisabledBackgroundColor = QColor(243, 243, 243);
    QColor m_menuItemForegroundColor = Qt::black;

    int m_nMenuItemSpacing = 2;
    int m_nMenuItemIconWH = 20;
    int m_nMenuItemHeight = 30;

    mutable bool m_hasIcon = false;
    mutable bool m_hasMenu = false;
};