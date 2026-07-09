#include "FluPMenuStyle.h"
#include <QStyleOptionMenuItem>
#include <QPainter>
#include "FluPMenu.h"
#include "../Utils/FluUtils.h"

void FluPMenuStyle::drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    if (element == PE_PanelMenu)
    {
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);

        painter->setPen(QColor(224, 224, 224));
        painter->setBrush(QColor(251, 251, 251));
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
                // Draw separator
                QColor separatorColor = QColor(0, 255, 0);
                painter->save();
                painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
                painter->setPen(QPen(separatorColor, 1));
                painter->drawLine(menuItem->rect.topLeft(), menuItem->rect.topRight());
                painter->restore();
                return;
            }

            QRect menuItemRect = menuItem->rect;
            /// background;
            menuItemRect =  menuItemRect.adjusted(2, 2, -2, -2);


            if (true)
            {
                QColor normalBackgroundColor = QColor(251, 251, 251);
                QColor hoverBackgroundColor = QColor(246, 246, 246);
                QColor disableBackgroundColor;

                QColor backgroundColor = normalBackgroundColor;
                if (menuItem->state & QStyle::State_Enabled)
                {
                    if ( (menuItem->state & QStyle::State_MouseOver) || (menuItem->state & QStyle::State_Selected) )
                    {
                        backgroundColor = hoverBackgroundColor;
                    }
                }
                else
                {
                    backgroundColor = disableBackgroundColor;
                }

                painter->save();
                painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
                painter->setPen(Qt::NoPen);
                painter->setBrush(backgroundColor);
                painter->drawRoundedRect(menuItemRect, 4, 4);
                painter->restore();
            }

            //bool hasIcon = false;
            /// icon;
            if (!menuItem->icon.isNull())
            {
                QRect iconRect;
                iconRect.setX(menuItemRect.x() + 2);
                iconRect.setY(menuItemRect.y() + (menuItemRect.height() - 20) / 2);
                painter->drawPixmap(iconRect, menuItem->icon.pixmap(20, 20));
                //hasIcon = true;
            }

            /// text;
            if (true)
            {
                QStringList texts = menuItem->text.split("\t");
                painter->save();
                painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
                painter->setPen(QColor(0, 0, 0));
                if (texts.size() == 2)
                {
                    QRect textRect;
                    if (m_hasIcon)
                    {
                        textRect.setX(menuItemRect.x() + 2 + 20 + 2);
                        textRect.setY(menuItemRect.y());
                        textRect.setWidth(menuItemRect.width() - 2 - 2 - 20 - 2);
                        if (m_hasMenu)
                        {
                            textRect.setWidth(textRect.width() - 20 - 2 -2);
                        }

                        textRect.setHeight(menuItemRect.height());
                        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, texts[0]);

                        QRect shortCutRect = textRect;
                        shortCutRect.setLeft(textRect.right() - menuItem->tabWidth - 4);
                        painter->drawText(shortCutRect, Qt::AlignLeft | Qt::AlignVCenter, texts[1]);
                    }
                    else
                    {
                        textRect.setX(menuItemRect.x() + 2);
                        textRect.setY(menuItemRect.y());
                        textRect.setWidth(menuItemRect.width() - 2);
                        if (m_hasMenu)
                        {
                            textRect.setWidth(textRect.width() - 20 - 2 - 2);
                        }

                        textRect.setHeight(menuItemRect.height());
                        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, texts[0]);

                        QRect shortCutRect = textRect;
                        shortCutRect.setLeft(textRect.right() - menuItem->tabWidth);
                        painter->drawText(shortCutRect, Qt::AlignLeft | Qt::AlignVCenter, texts[1]);
                    }
                }
                else if (texts.size() == 1)
                {
                    if (m_hasIcon)
                    {
                        QRect textRect;
                        textRect.setX(menuItemRect.x() + 2 + 20 + 2);
                        textRect.setY(menuItemRect.y());
                        textRect.setWidth(menuItemRect.width() - 2);
                        if (m_hasMenu)
                        {
                            textRect.setWidth(textRect.width() - 20 - 2 - 2);
                        }

                        textRect.setHeight(menuItemRect.height());
                        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, texts[0]);
                    }
                    else
                    {
                        QRect textRect;
                        textRect.setX(menuItemRect.x() + 2);
                        textRect.setY(menuItemRect.y());
                        textRect.setWidth(menuItemRect.width() - 2);
                        if (m_hasMenu)
                        {
                            textRect.setWidth(textRect.width() - 20 - 2 - 2);
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
                    painter->drawPixmap(menuItemRect.right() - 22, menuItemRect.y() + (menuItemRect.height() - 20) / 2,
                        FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChevronRight, QColor(8,8,8), 20, 20));
                    painter->restore();
                }
            }

            return;
        }

        return QProxyStyle::drawControl(element, option, painter, widget);
    }
    //return QProxyStyle::drawControl(element, option, painter, widget);
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
            QSize contentsSize =  QProxyStyle::sizeFromContents(type, menuItemOption, size, widget);
            
            const FluPMenu* menu = qobject_cast<const FluPMenu*>(widget);
            if (menu != nullptr && (menu->hasChildIcon() || menuItemOption->menuHasCheckableItems))
            {
                m_hasIcon = true;
            }
            
            contentsSize.setHeight(m_nMenuItemHeight);

            if (menu->hasChildMenu())
            {
                m_hasMenu = true;
                contentsSize.setWidth(contentsSize.width() + 20);
            }

            return contentsSize;
        }
        return QProxyStyle::sizeFromContents(type, option, size, widget);
    }

    return QProxyStyle::sizeFromContents(type, option, size, widget);
}
