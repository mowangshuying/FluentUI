#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QEvent>
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

class FluChangeBackgroundWidget : public QWidget
{
	Q_OBJECT
public:
	FluChangeBackgroundWidget(QWidget* parent = nullptr) : QWidget(parent)
	{
		m_normalBgColor = QColor("#1994e1");
		m_hoverBgColor = QColor("#d1eaf9");
		m_bHover = false;
		setMouseTracking(true);
		qDebug() << __FUNCTION__;
	}

	~FluChangeBackgroundWidget()
	{
		qDebug() << __FUNCTION__;
	}

protected:
	void enterEvent(QEnterEvent* event)
	{
		m_bHover = true;
		update();
	}

	void leaveEvent(QEvent* event)
	{
		m_bHover = false;
		update();
	}

	void paintEvent(QPaintEvent* event)
	{
		QWidget::paintEvent(event);
		QPainter painter(this);
		if (m_bHover)
		{
			qDebug() << "hover it!";
			painter.fillRect(rect(), m_normalBgColor);

		}
		else
		{
			qDebug() << "not hover it!";
			painter.fillRect(rect(), m_hoverBgColor);
		}
	}
private:
	bool   m_bHover;
	QColor m_normalBgColor;
	QColor m_hoverBgColor;
};

