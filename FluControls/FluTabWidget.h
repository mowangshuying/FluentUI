#pragma once

#include <QTableWidget>
#include "../FluUtils/FluStyleSheetUitls.h"

class FluTabWidget : public QTabWidget
{
	Q_OBJECT
public:
	FluTabWidget(QWidget* parent = nullptr) : QTabWidget(parent)
	{
		QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/FluTabWidget.qss");
		setStyleSheet(qss);
	}
};

