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

	QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget = nullptr) const override;
protected:
    QColor m_menuBarItemNormalBackgroundColor = Qt::white;
	QColor m_menuBarItemSelectedBackgroundColor = QColor(234, 234, 234);
    QColor m_menuBarItemPressedBackgroundColor = QColor(234, 234, 234);
    QColor m_menuBarItemDisabledBackgroundColor;
	QColor m_menuBarItemForegroundColor = Qt::black;
	int m_menuBarItemMargin = 5;
	int m_menuBarItemIconWH = 20;
};

