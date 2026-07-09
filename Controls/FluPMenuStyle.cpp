#include "FluPMenuStyle.h"
#include <QStyleOptionMenuItem>
#include <QPainter>

void FluPMenuStyle::drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    if (element == PE_PanelMenu)
    {
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);

        painter->setPen(QColor(224, 224, 224));
        painter->setBrush(QColor(251, 0, 251));
        painter->drawRoundedRect(option->rect, 4, 4);
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
            menuItemRect =  menuItemRect.adjusted(4, 4, -4, -4);


            if (true)
            {
                QColor normalBackgroundColor = QColor(251, 251, 251);
                QColor hoverBackgroundColor;
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
            /// icon;
            if (!menuItem->icon.isNull())
            {
                /// icon rect;
                /// now just draw it; optimize it later
                painter->drawPixmap(0, 0, menuItem->icon.pixmap(20, 20));
            }

            /// text;
            if (true)
            {
                QStringList texts = menuItem->text.split("\t");
                painter->save();
                painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
                painter->setPen(QColor(0, 0, 0));// text color
                painter->drawText(menuItemRect, Qt::AlignCenter, texts[0]);
                painter->restore();
            }

            /// expand icon;
            if (true)
            {

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
            contentsSize.setHeight(m_nMenuItemHeight);
            return contentsSize;
        }
        return QProxyStyle::sizeFromContents(type, option, size, widget);
    }

    return QProxyStyle::sizeFromContents(type, option, size, widget);
}
