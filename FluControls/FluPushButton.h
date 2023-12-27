#pragma once

#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>

#include "../FluUtils/FluStyleSheetUitls.h"

class FluPushButton : public QPushButton
{
	Q_OBJECT
public:
	FluPushButton(QWidget* parent = nullptr) : QPushButton(parent)
	{
		setFixedSize(200, 30);
		QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/FluPushButton.qss");
		setStyleSheet(qss);
	}
protected:
};