#pragma once

#include <QMenu>
#include <QWidget>
#include "FluPMenuStyle.h"
#include "../Utils/FluUtils.h"

class FluPMenu : public QMenu
{
    Q_OBJECT
    Q_PROPERTY(QColor ppMenuBackgroundColor READ getMenuBackgroundColor WRITE setMenuBackgroundColor)
    Q_PROPERTY(QColor ppMenuBorderColor READ getMenuBoderColor WRITE setMenuBoderColor)
    Q_PROPERTY(QColor ppMenuItemNormalBackgroundColor READ getMenuItemNormalBackgroundColor WRITE setMenuItemNormalBackgroundColor)
    Q_PROPERTY(QColor ppMenuItemSelectedBackgroundColor READ getMenuItemSelectedBackgroundColor WRITE setMenuItemSelectedBackgroundColor)
    Q_PROPERTY(QColor ppMenuItemDisabledBackgroundColor READ getMenuItemDisabledBackgroundColor WRITE setMenuItemDisabledBackgroundColor)
    Q_PROPERTY(QColor ppMenuItemForegroundColor READ getMenuItemForegroundColor WRITE setMenuItemForegroundColor)
    Q_PROPERTY(int ppMenuItemSpacing READ getMenuItemSpacing WRITE setMenuItemSpacing)
    Q_PROPERTY(int ppMenuItemIconWH READ getMenuItemIconWH WRITE setMenuItemIconWH)
    Q_PROPERTY(int ppMenuItemHeight READ getMenuItemHeight WRITE setMenuItemHeight)
  public:
    FluPMenu(QWidget *parent = nullptr);

    FluPMenu(const QString &title, QWidget *parent = nullptr);

    QColor getMenuBackgroundColor() const
    {
        return m_style->getMenuBackgroundColor();
    }

    void setMenuBackgroundColor(const QColor &color)
    {
        m_style->setMenuBackgroundColor(color);
    }

    QColor getMenuBoderColor() const
    {
        return m_style->getMenuBoderColor();
    }

    void setMenuBoderColor(const QColor &color)
    {
        m_style->setMenuBoderColor(color);
    }

    QColor getMenuItemNormalBackgroundColor() const
    {
        return m_style->getMenuItemNormalBackgroundColor();
    }

    void setMenuItemNormalBackgroundColor(const QColor &color)
    {
        m_style->setMenuItemNormalBackgroundColor(color);
    }

    QColor getMenuItemSelectedBackgroundColor() const
    {
        return m_style->getMenuItemSelectedBackgroundColor();
    }

    void setMenuItemSelectedBackgroundColor(const QColor &color)
    {
        m_style->setMenuItemSelectedBackgroundColor(color);
    }

    QColor getMenuItemDisabledBackgroundColor() const
    {
        return m_style->getMenuItemDisabledBackgroundColor();
    }

    void setMenuItemDisabledBackgroundColor(const QColor &color)
    {
        m_style->setMenuItemDisabledBackgroundColor(color);
    }

    QColor getMenuItemForegroundColor() const
    {
        return m_style->getMenuItemForegroundColor();
    }

    void setMenuItemForegroundColor(const QColor &color)
    {
        m_style->setMenuItemForegroundColor(color);
    }

    int getMenuItemSpacing() const
    {
        return m_style->getMenuItemSpacing();
    }

    void setMenuItemSpacing(int spacing)
    {
        m_style->setMenuItemSpacing(spacing);
    }

    int getMenuItemIconWH() const
    {
        return m_style->getMenuItemIconWH();
    }

    void setMenuItemIconWH(int iconWH)
    {
        m_style->setMenuItemIconWH(iconWH);
    }

    int getMenuItemHeight() const
    {
        return m_style->getMenuItemHeight();
    }

    void setMenuItemHeight(int height)
    {
        m_style->setMenuItemHeight(height);
    }

    QAction *addMenu(QMenu *menu)
    {
        return QMenu::addMenu(menu);
    }

    QMenu *addMenu(const QString &title)
    {
        // return QMenu::addMenu(title);
        FluPMenu *menu = new FluPMenu(title, this);
        QMenu::addAction(menu->menuAction());
        return menu;
    }

    bool hasChildMenu() const
    {
        for (auto action : actions())
        {
            if (action->menu())
            {
                return true;
            }
        }

        return false;
    }

    bool hasChildIcon() const
    {
        for (auto action : actions())
        {
            if (!action->icon().isNull())
            {
                return true;
            }
        }

        return false;
    }

  public slots:
    void onThemeChanged();

  protected:
    FluPMenuStyle *m_style = nullptr;
};