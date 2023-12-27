#pragma once

#include <QWidget>
#include <QHBoxLayout>

class FluExpandDemo : public QWidget
{
	Q_OBJECT
public:
	FluExpandDemo(QWidget* parent = nullptr) : QWidget(parent)
	{
		auto hLayout = new QHBoxLayout(this);
		auto widget1 = new QWidget(this);
		auto widget2 = new QWidget(this);

		widget1->setFixedWidth(320);
		hLayout->addWidget(widget1);
		hLayout->addWidget(widget2);
	}
};

