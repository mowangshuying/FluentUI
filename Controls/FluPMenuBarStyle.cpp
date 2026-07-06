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

void FluPMenuBarStyle::drawMenuBarItem(const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
	QStyleOptionMenuItem* opt = (QStyleOptionMenuItem*)option;
	if (opt->menuItemType == QStyleOptionMenuItem::Separator)
	{
		return;
	}

	FluPMenuBar* menuBar = (FluPMenuBar*)(widget);
	QRect rect = option->rect;
	

	//QColor bc;

	// draw backgound
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
        //FluPPUtils::setPPMouseState(menuBar, "menuBarItem", FluPPUtils::PPMouseState::Disabled);
		menuBarItemBackgroundColor = m_menuBarItemDisabledBackgroundColor;
	}

    painter->setBrush(menuBarItemBackgroundColor);
	painter->drawRoundedRect(rect, 4, 4);
	painter->restore();

	/// draw icon;
	if (menuBar != nullptr)
	{
		FluAction* action = qobject_cast<FluAction*>(menuBar->actionAt(option->rect.center()));
		if (action != nullptr)
		{
			/// icon & text;
            //QColor penColor;
            QPixmap icon;
			// int nWH = 16;
			if (action->getAwesomeType() != FluAwesomeType::None)
			{
                icon = FluIconUtils::getFluentIconPixmap(action->getAwesomeType(), FluThemeUtils::getUtils()->getTheme());
			}
			else if (!opt->icon.isNull())
			{
                icon = opt->icon.pixmap(QSize(m_menuBarItemIconWH, m_menuBarItemIconWH));
			}

			QString text = opt->text;
			text = text.replace("&", "");
			// only draw icon
			if (!icon.isNull() && text.isEmpty())
			{
				painter->drawPixmap(opt->rect, icon);
			}
            else if (!text.isEmpty() && icon.isNull())
			{
				painter->save();
				painter->setPen(m_menuBarItemForegroundColor);
				painter->drawText(opt->rect, Qt::AlignCenter, text);
				painter->restore();
			}
			else if (!text.isEmpty() && !icon.isNull())
			{
				QRect  rect;
				rect.setX(opt->rect.x());
				rect.setY(opt->rect.y() + (opt->rect.height() - m_menuBarItemIconWH) / 2);
                rect.setWidth(m_menuBarItemIconWH);
                rect.setHeight(m_menuBarItemIconWH);
                painter->drawPixmap(rect, icon);

				// text
                painter->save();
                painter->setPen(m_menuBarItemForegroundColor);
				rect.setX(opt->rect.x() + m_menuBarItemIconWH);
				rect.setY(opt->rect.y());
                rect.setWidth(opt->rect.width() - m_menuBarItemIconWH);
                rect.setHeight(opt->rect.height());
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
        return QProxyStyle::drawControl(element, option, painter, widget);
}

QSize FluPMenuBarStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const
{
    if (type == QStyle::CT_MenuBar)
	{
		QSize menuBarSize = QProxyStyle::sizeFromContents(type, option, size, widget);
		menuBarSize.setHeight(menuBarSize.height());
		return menuBarSize;

	}
	else if (type == QStyle::CT_MenuBarItem)
	{
		QStyleOptionMenuItem* opt = (QStyleOptionMenuItem*)option;
		QSize menuItemSize = QProxyStyle::sizeFromContents(type, option, size, widget);
		menuItemSize.setWidth(menuItemSize.width() + 2 * m_menuBarItemMargin);
		if (!opt->icon.isNull())
		{
			menuItemSize.setWidth(menuItemSize.width() + m_menuBarItemIconWH);
		}
		return menuItemSize;
	}
	return QProxyStyle::sizeFromContents(type, option, size, widget);
}
