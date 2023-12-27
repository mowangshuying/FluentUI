#pragma once

#include <QWidget>

#include <QPainter>
#include <QStyleOption>
#include "../FluUtils/FluStyleSheetUitls.h"

class FluHomePage : public QWidget
{
	Q_OBJECT
public:
	FluHomePage(QWidget* parent = nullptr) : QWidget(parent)
	{
		QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/FluHomePage.qss");
		setStyleSheet(qss);
	}

	void paintEvent(QPaintEvent* event)
	{
		QStyleOption opt;
		opt.initFrom(this);
		QPainter painter(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
	}
};

