#include "FluPMenuBar.h"
#include "FluPMenuBarStyle.h"


FluPMenuBar::FluPMenuBar(QWidget *parent)
	: QMenuBar(parent)
{
	m_style = new FluPMenuBarStyle(style());
    setStyle(m_style);
}

FluPMenuBar::~FluPMenuBar()
{
}
