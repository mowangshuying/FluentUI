#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QEvent>
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

class FluChangeBgDemo : public QWidget
{
	Q_OBJECT
public:
	FluChangeBgDemo(QWidget* parent = nullptr);

	~FluChangeBgDemo();

protected:
	void enterEvent(QEnterEvent* event);

	void leaveEvent(QEvent* event);

	void paintEvent(QPaintEvent* event);
private:
	bool   m_bHover;
	QColor m_normalBgColor;
	QColor m_hoverBgColor;
};

