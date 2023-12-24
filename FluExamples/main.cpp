#include <QApplication>
#include "FluChangeBackgroundWidget.h"
#include "FluExampleTabWidget.h"
int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	//FluChangeBackgroundWidget demo;
	//demo.show();

	FluExampleTabWidget demo;
	demo.show();


	return app.exec();
}