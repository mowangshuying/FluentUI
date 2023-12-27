#pragma once

#include "../FluControls/FluFrameLessWidget.h"
#include "../FluControls/FluNavigationView.h"
#include "FluHomePage.h"
#include <QStackedLayout>

class FluGalleryWindow : public FluFrameLessWidget
{
	Q_OBJECT
public:
	FluGalleryWindow(QWidget* parent = nullptr);

protected:
	FluNavigationView* m_navView;
	QStackedLayout* m_sLayout;
};

