#pragma once

#include <QProxyStyle>

class FluPMenuBarStyle  : public QProxyStyle
{
	Q_OBJECT

public:
	FluPMenuBarStyle(QStyle *parent = nullptr);
	~FluPMenuBarStyle();

	QColor getMenuBarItemNormalBackgroundColor() const;
	QColor getMenuBarItemSelectedBackgroundColor() const;
	QColor getMenuBarItemPressedBackgroundColor() const;
	QColor getMenuBarItemDisabledBackgroundColor() const;
	QColor getMenuBarItemForegroundColor() const;
	int getMenuBarItemMargin() const;
	int getMenuBarItemIconWH() const;
	int getMenuBarItemHeight() const;

	void setMenuBarItemNormalBackgroundColor(const QColor &color);
	void setMenuBarItemSelectedBackgroundColor(const QColor &color);
	void setMenuBarItemPressedBackgroundColor(const QColor &color);
	void setMenuBarItemDisabledBackgroundColor(const QColor &color);
	void setMenuBarItemForegroundColor(const QColor &color);
	void setMenuBarItemMargin(int margin);
	void setMenuBarItemIconWH(int iconWH);
	void setMenuBarItemHeight(int height);

	void drawMenuBarItem(const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const;

	/// draw Primitive
	/// static draw;
	void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;

	/// draw Control
	/// dynamic draw;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;

	QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget = nullptr) const override;
protected:
    QColor m_menuBarItemNormalBackgroundColor = QColor(243, 243, 243);
	QColor m_menuBarItemSelectedBackgroundColor = QColor(234, 234, 234);
    QColor m_menuBarItemPressedBackgroundColor = QColor(234, 234, 234);
    QColor m_menuBarItemDisabledBackgroundColor;
	QColor m_menuBarItemForegroundColor = Qt::black;
	int m_menuBarItemMargin = 2;
	int m_menuBarItemIconWH = 20;
	int m_menuBarItemHeight = 24;
};

