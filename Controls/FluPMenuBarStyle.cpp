#include "FluPMenuBarStyle.h"
#include <QStyleOptionMenuItem>
#include <QPainter>
#include "FluPMenuBar.h"
#include "../Utils/FluUtils.h"
#include "FluAction.h"

FluPMenuBarStyle::FluPMenuBarStyle(QStyle *parent /* = nullptr*/)
	: QProxyStyle(parent)
{
}

FluPMenuBarStyle::~FluPMenuBarStyle()
{
}

QColor FluPMenuBarStyle::getMenuBarItemNormalBackgroundColor() const
{
    return m_menuBarItemNormalBackgroundColor;
}

QColor FluPMenuBarStyle::getMenuBarItemSelectedBackgroundColor() const
{
    return m_menuBarItemSelectedBackgroundColor;
}

QColor FluPMenuBarStyle::getMenuBarItemPressedBackgroundColor() const
{
    return m_menuBarItemPressedBackgroundColor;
}

QColor FluPMenuBarStyle::getMenuBarItemDisabledBackgroundColor() const
{
    return m_menuBarItemDisabledBackgroundColor;
}

QColor FluPMenuBarStyle::getMenuBarItemForegroundColor() const
{
	return m_menuBarItemForegroundColor;
}

int FluPMenuBarStyle::getMenuBarItemMargin() const
{
    return m_menuBarItemMargin;
}

int FluPMenuBarStyle::getMenuBarItemIconWH() const
{
    return m_menuBarItemIconWH;
}

int FluPMenuBarStyle::getMenuBarItemHeight() const
{
    return m_menuBarItemHeight;
}

void FluPMenuBarStyle::setMenuBarItemNormalBackgroundColor(const QColor &color)
{
    m_menuBarItemNormalBackgroundColor = color;
}

void FluPMenuBarStyle::setMenuBarItemSelectedBackgroundColor(const QColor &color)
{
    m_menuBarItemSelectedBackgroundColor = color;
}

void FluPMenuBarStyle::setMenuBarItemPressedBackgroundColor(const QColor &color)
{
    m_menuBarItemPressedBackgroundColor = color;
}

void FluPMenuBarStyle::setMenuBarItemDisabledBackgroundColor(const QColor &color)
{
    m_menuBarItemDisabledBackgroundColor = color;
}

void FluPMenuBarStyle::setMenuBarItemForegroundColor(const QColor &color)
{
	m_menuBarItemForegroundColor = color;
}

void FluPMenuBarStyle::setMenuBarItemMargin(int margin)
{
    m_menuBarItemMargin = margin;
}

void FluPMenuBarStyle::setMenuBarItemIconWH(int iconWH)
{
    m_menuBarItemIconWH = iconWH;
}

void FluPMenuBarStyle::setMenuBarItemHeight(int height)
{
    m_menuBarItemHeight = height;
}

void FluPMenuBarStyle::drawMenuBarItem(const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
	QStyleOptionMenuItem* opt = (QStyleOptionMenuItem*)option;
	if (opt->menuItemType == QStyleOptionMenuItem::Separator)
	{
		return;
	}

	FluPMenuBar* menuBar = (FluPMenuBar*)(widget);
	if (menuBar == nullptr)
	{
		return;
	}


	if (true)
	{
		int nMenuBarHeight = menuBar->height();
		QRect newRect = option->rect;
		painter->save();
		painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		painter->setPen(Qt::NoPen);
		painter->setBrush(m_menuBarItemNormalBackgroundColor);
		painter->drawRect(newRect);
		painter->restore();
	}


	int nMenuBarHeight = menuBar->height();
	QRect newRect = option->rect;
	newRect.setY((nMenuBarHeight - m_menuBarItemHeight) / 2);
	newRect.setHeight(m_menuBarItemHeight);
	if (true)
	{
		painter->save();
		painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		painter->setPen(Qt::NoPen);
	
		QColor menuBarItemBackgroundColor = m_menuBarItemNormalBackgroundColor;
		if (opt->state & QStyle::State_Enabled)
		{
			if (opt->state & QStyle::State_Sunken)
			{
				menuBarItemBackgroundColor = m_menuBarItemPressedBackgroundColor;
			}
			else if (opt->state & QStyle::State_Selected)
			{
				menuBarItemBackgroundColor = m_menuBarItemSelectedBackgroundColor;
			}
		}
		else
		{
			menuBarItemBackgroundColor = m_menuBarItemDisabledBackgroundColor;
		}

		painter->setBrush(menuBarItemBackgroundColor);
		painter->drawRoundedRect(newRect, 4, 4);
		painter->restore();
	}

	

	/// draw icon;
	if (menuBar != nullptr)
	{
		QAction* action = menuBar->actionAt(newRect.center());
		if (action != nullptr)
		{
            QPixmap icon;
			if (!opt->icon.isNull())
			{
                icon = opt->icon.pixmap(QSize(m_menuBarItemIconWH, m_menuBarItemIconWH));
			}

			QString text = opt->text;
			text = text.replace("&", "");
			if (!icon.isNull() && text.isEmpty())
			{
				painter->drawPixmap(opt->rect, icon);
			}
            else if (!text.isEmpty() && icon.isNull())
			{
				painter->save();
				painter->setPen(m_menuBarItemForegroundColor);
				painter->drawText(newRect, Qt::AlignCenter, text);
				painter->restore();
			}
			else if (!text.isEmpty() && !icon.isNull())
			{
				int textLength = opt->fontMetrics.horizontalAdvance(text);
				int nSpace = (newRect.width() - (2 * m_menuBarItemMargin + m_menuBarItemIconWH) - textLength) / 2;

				QRect  rect;
				rect.setX(newRect.x() + m_menuBarItemMargin + nSpace);
				rect.setY(newRect.y() + (newRect.height() - m_menuBarItemIconWH) / 2);
                rect.setWidth(m_menuBarItemIconWH);
                rect.setHeight(m_menuBarItemIconWH);
                painter->drawPixmap(rect, icon);

				// text
                painter->save();
                painter->setPen(m_menuBarItemForegroundColor);
				rect.setX(newRect.x() + m_menuBarItemIconWH + m_menuBarItemMargin + nSpace);
				rect.setY(newRect.y());
                rect.setWidth(newRect.width() - m_menuBarItemIconWH - 2 * m_menuBarItemMargin - nSpace);
                rect.setHeight(newRect.height());


				// calc text length
				QFontMetrics fm(painter->font());
                painter->drawText(rect, Qt::AlignCenter, text);
				painter->restore();
			}
		}
	}
}

void FluPMenuBarStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    return QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void FluPMenuBarStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
	if (element == CE_MenuBarItem)
	{
        return drawMenuBarItem(option, painter, widget);
	}
	else if (element == QStyle::CE_MenuBarEmptyArea)
	{
		painter->save();
		painter->setPen(Qt::NoPen);
		painter->setBrush(m_menuBarItemNormalBackgroundColor);
		painter->drawRect(option->rect);
		painter->restore();
		return;
	}
    return QProxyStyle::drawControl(element, option, painter, widget);
}

QSize FluPMenuBarStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const
{
    if (type == QStyle::CT_MenuBar)
	{
		QSize menuBarSize = QProxyStyle::sizeFromContents(type, option, size, widget);
		menuBarSize.setHeight(widget->height());
		return menuBarSize;

	}
	else if (type == QStyle::CT_MenuBarItem)
	{
		QStyleOptionMenuItem* opt = (QStyleOptionMenuItem*)option;
		QSize menuItemSize; 
		menuItemSize.setHeight(widget->height());
		menuItemSize.setWidth(menuItemSize.width() + 2 * m_menuBarItemMargin);
		if (!opt->icon.isNull())
		{
			menuItemSize.setWidth(menuItemSize.width() + m_menuBarItemIconWH);
		}

		menuItemSize.setWidth(menuItemSize.width() + opt->fontMetrics.horizontalAdvance(opt->text));
		return menuItemSize;
	}
	return QProxyStyle::sizeFromContents(type, option, size, widget);
}
