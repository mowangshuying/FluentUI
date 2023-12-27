#include <QWidget>
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "../FluUtils/FluIconUtils.h"
#include "FluIconToolWidget.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	FluIconToolWidget w;
	w.show();

	return app.exec();
}