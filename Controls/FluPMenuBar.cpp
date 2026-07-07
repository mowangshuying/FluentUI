#include "FluPMenuBar.h"
#include "FluPMenuBarStyle.h"
#include  "../Utils/FluUtils.h"

FluPMenuBar::FluPMenuBar(QWidget *parent)
	: QMenuBar(parent)
{
	setPMenuBarFontSize(13);
	m_style = new FluPMenuBarStyle(style());
    setStyle(m_style);
	setFixedHeight(30);
	onThemeChanged();
	connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) {
		onThemeChanged();
	});
}

FluPMenuBar::~FluPMenuBar()
{
}

void FluPMenuBar::setPMenuBarFontSize(int size)
{
	QFont tmpFont = font();
	tmpFont.setPixelSize(size);
	setFont(tmpFont);
}

void FluPMenuBar::onThemeChanged()
{
	FluStyleSheetUitls::setQssByFileName("FluPMenuBar.qss", this, FluThemeUtils::getUtils()->getTheme());
	style()->polish(this);
}
