#pragma once

#include <QMenu>
#include <QWidget>
#include "FluPMenuStyle.h"

class FluPMenu : public QMenu
{
    Q_OBJECT
public:
    FluPMenu(QWidget *parent = nullptr) : QMenu(parent)
    {
        setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);
        setStyle(new FluPMenuStyle);
    }

    FluPMenu(const QString &title, QWidget *parent = nullptr) : FluPMenu(parent)
    {
        setTitle(title);
    }

    QAction* addMenu(QMenu *menu)
    {
        return QMenu::addMenu(menu);
    }

    QMenu* addMenu(const QString &title)
    {
        // return QMenu::addMenu(title);
        FluPMenu* menu = new FluPMenu(title, this);
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


    // Event;
    void showEvent(QShowEvent *event) override
    {
        QMenu::showEvent(event);
    }

    void paintEvent(QPaintEvent *event) override
    {
        QMenu::paintEvent(event);
    }

protected:
};