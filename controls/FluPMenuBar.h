#pragma once

#include <QMenuBar>
#include "FluPMenuBarStyle.h"
// class FluPMenuBarStyle;

class FluPMenuBar : public QMenuBar
{
    Q_OBJECT
    Q_PROPERTY(QColor ppMenuBarItemNormalBackgroundColor READ getMenuBarItemNormalBackgroundColor WRITE setMenuBarItemNormalBackgroundColor)
    Q_PROPERTY(QColor ppMenuBarItemSelectedBackgroundColor READ getMenuBarItemSelectedBackgroundColor WRITE setMenuBarItemSelectedBackgroundColor)
    Q_PROPERTY(QColor ppMenuBarItemPressedBackgroundColor READ getMenuBarItemPressedBackgroundColor WRITE setMenuBarItemPressedBackgroundColor)
    Q_PROPERTY(QColor ppMenuBarItemDisabledBackgroundColor READ getMenuBarItemDisabledBackgroundColor WRITE setMenuBarItemDisabledBackgroundColor)
    Q_PROPERTY(QColor ppMenuBarItemForegroundColor READ getMenuBarItemForegroundColor WRITE setMenuBarItemForegroundColor)
    Q_PROPERTY(int ppMenuBarItemIconWH READ getMenuBarItemIconWH WRITE setMenuBarItemIconWH)
    Q_PROPERTY(int ppMenuBarItemMargin READ getMenuBarItemMargin WRITE setMenuBarItemMargin)
    Q_PROPERTY(int ppMenuBarItemHeight READ getMenuBarItemHeight WRITE setMenuBarItemHeight)

  public:
    FluPMenuBar(QWidget *parent = nullptr);
    ~FluPMenuBar();

    void setPMenuBarFontSize(int size);

    /// pp properties
    QColor getMenuBarItemNormalBackgroundColor() const
    {
        return m_style->getMenuBarItemNormalBackgroundColor();
    }
    QColor getMenuBarItemSelectedBackgroundColor() const
    {
        return m_style->getMenuBarItemSelectedBackgroundColor();
    }
    QColor getMenuBarItemPressedBackgroundColor() const
    {
        return m_style->getMenuBarItemPressedBackgroundColor();
    }
    QColor getMenuBarItemDisabledBackgroundColor() const
    {
        return m_style->getMenuBarItemDisabledBackgroundColor();
    }
    QColor getMenuBarItemForegroundColor() const
    {
        return m_style->getMenuBarItemForegroundColor();
    }
    int getMenuBarItemMargin() const
    {
        return m_style->getMenuBarItemMargin();
    }
    int getMenuBarItemIconWH() const
    {
        return m_style->getMenuBarItemIconWH();
    }
    int getMenuBarItemHeight() const
    {
        return m_style->getMenuBarItemHeight();
    }

    void setMenuBarItemNormalBackgroundColor(const QColor &color)
    {
        m_style->setMenuBarItemNormalBackgroundColor(color);
    }
    void setMenuBarItemSelectedBackgroundColor(const QColor &color)
    {
        m_style->setMenuBarItemSelectedBackgroundColor(color);
    }
    void setMenuBarItemPressedBackgroundColor(const QColor &color)
    {
        m_style->setMenuBarItemPressedBackgroundColor(color);
    }
    void setMenuBarItemDisabledBackgroundColor(const QColor &color)
    {
        m_style->setMenuBarItemDisabledBackgroundColor(color);
    }
    void setMenuBarItemForegroundColor(const QColor &color)
    {
        m_style->setMenuBarItemForegroundColor(color);
    }
    void setMenuBarItemMargin(int margin)
    {
        m_style->setMenuBarItemMargin(margin);
    }
    void setMenuBarItemIconWH(int iconWH)
    {
        m_style->setMenuBarItemIconWH(iconWH);
    }
    void setMenuBarItemHeight(int height)
    {
        m_style->setMenuBarItemHeight(height);
    }

  public slots:
    void onThemeChanged();

  protected:
    FluPMenuBarStyle *m_style;
};
