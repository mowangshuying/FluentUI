#pragma once

#include <QProxyStyle>

class FluPMenuBarStyle  : public QProxyStyle
{
	Q_OBJECT

public:
	FluPMenuBarStyle(QStyle *parent = nullptr);
	~FluPMenuBarStyle();

	void drawMenuBarItem(const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const;

	/// draw Primitive
	/// static draw;
	void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;

	/// draw Control
	/// dynamic draw;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;

protected:
    QColor m_menuBarItemNormalBackgroundColor;
	QColor m_menuBarItemSelectedBackgroundColor;
    QColor m_menuBarItemPressedBackgroundColor;
    QColor m_menuBarItemDisabledBackgroundColor;
};

