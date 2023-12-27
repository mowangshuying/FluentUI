#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QStyleOption>
#include "../FluControls/FluPushButton.h"

class FluButtonDemo : public QWidget
{
	Q_OBJECT
public:
	FluButtonDemo(QWidget* parent = nullptr);

protected:
	void paintEvent(QPaintEvent* paintEvent);
};

