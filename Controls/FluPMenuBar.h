#pragma once

#include <QMenuBar>

class FluPMenuBarStyle;

class FluPMenuBar : public QMenuBar
{
	Q_OBJECT

public:
	FluPMenuBar(QWidget *parent = nullptr);
	~FluPMenuBar();

protected:
	FluPMenuBarStyle* m_style;
};
