#include "FluPMenuStyle.h"
#include <QStyleOptionMenuItem>
#include <QPainter>

void FluPMenuStyle::drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
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
                QColor separatorColor;
                painter->save();
                painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
                painter->setPen(QPen(separatorColor, 1));
                painter->drawLine(menuItem->rect.topLeft(), menuItem->rect.topRight());
                painter->restore();
                return;
            }

            QRect menuItemRect = menuItem->rect;
            /// background;

            if (true)
            {
                QColor normalBackgroundColor = QColor(243, 0, 243);
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
                painter->setPen(Qt::NoPen);
                painter->setBrush(backgroundColor);
                painter->drawRect(menuItemRect);
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
                painter->drawText(menuItemRect, Qt::AlignLeft | Qt::AlignVCenter, texts[0]);
                painter->restore();
            }

            /// expand icon;
            if (true)
            {

            }

        }

        return QProxyStyle::drawControl(element, option, painter, widget);
    }
    return QProxyStyle::drawControl(element, option, painter, widget);
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
