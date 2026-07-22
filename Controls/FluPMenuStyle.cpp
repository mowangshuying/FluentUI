#include "FluPMenuStyle.h"
#include <QStyleOptionMenuItem>
#include <QPainter>
#include "FluPMenu.h"
#include "../Utils/FluUtils.h"

FluPMenuStyle::FluPMenuStyle(QStyle* baseStyle) : QProxyStyle(baseStyle)
{
}

void FluPMenuStyle::drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    if (element == PE_PanelMenu)
    {
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
        painter->setPen(m_menuBorderColor);
        painter->setBrush(m_menuBackgroundColor);
        painter->drawRoundedRect(option->rect, 6, 6);
        painter->restore();
        return;
    }
    return QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void FluPMenuStyle::drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    if (element == CE_MenuItem)
    {
        const QStyleOptionMenuItem* menuItem = qstyleoption_cast<const QStyleOptionMenuItem*>(option);
        if (menuItem != nullptr)
        {
            // Custom drawing code for menu items
            if (menuItem->menuItemType == QStyleOptionMenuItem::Separator)
            {
                painter->save();
                painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
                painter->setPen(QPen(m_menuBorderColor, 1));
                painter->drawLine(menuItem->rect.topLeft(), menuItem->rect.topRight());
                painter->restore();
                return;
            }

            QRect menuItemRect = menuItem->rect;

            /// background;
            menuItemRect = menuItemRect.adjusted(m_nMenuItemSpacing, m_nMenuItemSpacing, -m_nMenuItemSpacing, -m_nMenuItemSpacing);
            if (true)
            {
                QColor backgroundColor = m_menuItemNormalBackgroundColor;
                if (menuItem->state & QStyle::State_Enabled)
                {
                    if ((menuItem->state & QStyle::State_MouseOver) || (menuItem->state & QStyle::State_Selected))
                    {
                        backgroundColor = m_menuItemSelectedBackgroundColor;
                    }
                }
                else
                {
                    backgroundColor = m_menuItemDisabledBackgroundColor;
                }

                painter->save();
                painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
                painter->setPen(Qt::NoPen);
                painter->setBrush(backgroundColor);
                painter->drawRoundedRect(menuItemRect, 4, 4);
                painter->restore();
            }

            if (!menuItem->icon.isNull())
            {
                QRect iconRect;
                iconRect.setX(menuItemRect.x() + m_nMenuItemSpacing);
                iconRect.setY(menuItemRect.y() + (menuItemRect.height() - m_nMenuItemIconWH) / 2);
                painter->drawPixmap(iconRect, menuItem->icon.pixmap(m_nMenuItemIconWH, m_nMenuItemIconWH));
            }

            if (true)
            {
                QStringList texts = menuItem->text.split("\t");
                painter->save();
                painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
                painter->setPen(m_menuItemForegroundColor);
                if (texts.size() == 2)
                {
                    QRect textRect;
                    if (m_hasIcon)
                    {
                        textRect.setX(menuItemRect.x() + m_nMenuItemSpacing + m_nMenuItemIconWH + m_nMenuItemSpacing);
                        textRect.setY(menuItemRect.y());
                        textRect.setWidth(menuItemRect.width() - (m_nMenuItemSpacing + m_nMenuItemIconWH + m_nMenuItemSpacing + m_nMenuItemSpacing));
                        if (m_hasMenu)
                        {
                            textRect.setWidth(textRect.width() - (m_nMenuItemSpacing + m_nMenuItemIconWH));
                        }

                        textRect.setHeight(menuItemRect.height());
                        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, texts[0]);

                        QRect shortCutRect = textRect;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
                        shortCutRect.setLeft(textRect.right() - menuItem->tabWidth);
#else
                        shortCutRect.setLeft(textRect.right() - menuItem->reservedShortcutWidth);
#endif
                        painter->drawText(shortCutRect, Qt::AlignLeft | Qt::AlignVCenter, texts[1]);
                    }
                    else
                    {
                        textRect.setX(menuItemRect.x() + m_nMenuItemSpacing);
                        textRect.setY(menuItemRect.y());
                        textRect.setWidth(menuItemRect.width() - (m_nMenuItemSpacing + m_nMenuItemSpacing));
                        if (m_hasMenu)
                        {
                            textRect.setWidth(textRect.width() - (m_nMenuItemSpacing + m_nMenuItemIconWH));
                        }

                        textRect.setHeight(menuItemRect.height());
                        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, texts[0]);

                        QRect shortCutRect = textRect;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
                        shortCutRect.setLeft(textRect.right() - menuItem->tabWidth);
#else
                        shortCutRect.setLeft(textRect.right() - menuItem->reservedShortcutWidth);
#endif
                        painter->drawText(shortCutRect, Qt::AlignLeft | Qt::AlignVCenter, texts[1]);
                    }
                }
                else if (texts.size() == 1)
                {
                    if (m_hasIcon)
                    {
                        QRect textRect;
                        textRect.setX(menuItemRect.x() + m_nMenuItemSpacing + m_nMenuItemIconWH + m_nMenuItemSpacing);
                        textRect.setY(menuItemRect.y());
                        textRect.setWidth(menuItemRect.width() - (m_nMenuItemSpacing + m_nMenuItemIconWH + m_nMenuItemSpacing + m_nMenuItemSpacing));
                        if (m_hasMenu)
                        {
                            textRect.setWidth(textRect.width() - (m_nMenuItemSpacing + m_nMenuItemIconWH));
                        }

                        textRect.setHeight(menuItemRect.height());
                        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, texts[0]);
                    }
                    else
                    {
                        QRect textRect;
                        textRect.setX(menuItemRect.x() + m_nMenuItemSpacing);
                        textRect.setY(menuItemRect.y());
                        textRect.setWidth(menuItemRect.width() - m_nMenuItemSpacing);
                        if (m_hasMenu)
                        {
                            textRect.setWidth(textRect.width() - (m_nMenuItemIconWH + m_nMenuItemSpacing));
                        }

                        textRect.setHeight(menuItemRect.height());
                        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, texts[0]);
                    }
                }
                painter->restore();
            }

            /// expand icon;
            if (true)
            {
                if (menuItem->menuItemType == QStyleOptionMenuItem::SubMenu)
                {
                    painter->save();
                    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
                    painter->drawPixmap(menuItemRect.right() - (m_nMenuItemIconWH + m_nMenuItemSpacing),
                                        menuItemRect.y() + (menuItemRect.height() - m_nMenuItemIconWH) / 2,
                                        FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChevronRight, FluThemeUtils::getUtils()->getTheme(), m_nMenuItemIconWH, m_nMenuItemIconWH));
                    painter->restore();
                }
            }

            return;
        }

        return QProxyStyle::drawControl(element, option, painter, widget);
    }
}

int FluPMenuStyle::pixelMetric(PixelMetric metric, const QStyleOption* option, const QWidget* widget) const
{
    return 0;
}

QSize FluPMenuStyle::sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const
{
    if (type == QStyle::CT_MenuItem)
    {
        const QStyleOptionMenuItem* menuItemOption = qstyleoption_cast<const QStyleOptionMenuItem*>(option);
        if (menuItemOption != nullptr && menuItemOption->menuItemType != QStyleOptionMenuItem::Separator)
        {
            QSize contentsSize = QProxyStyle::sizeFromContents(type, menuItemOption, size, widget);

            const FluPMenu* menu = qobject_cast<const FluPMenu*>(widget);
            if (menu != nullptr && (menu->hasChildIcon() || menuItemOption->menuHasCheckableItems))
            {
                m_hasIcon = true;
            }

            contentsSize.setHeight(m_nMenuItemHeight);

            if (menu != nullptr && menu->hasChildMenu())
            {
                m_hasMenu = true;
                contentsSize.setWidth(contentsSize.width() + m_nMenuItemSpacing + m_nMenuItemIconWH);
            }

            return contentsSize;
        }
        return QProxyStyle::sizeFromContents(type, option, size, widget);
    }

    return QProxyStyle::sizeFromContents(type, option, size, widget);
}
