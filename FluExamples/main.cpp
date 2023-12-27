#include <QApplication>
#include "FluChangeBgDemo.h"
#include "FluTabDemo.h"
#include "FluButtonDemo.h"
#include "../FluControls/FluNavigationView.h"
#include "FluNavigationDemo.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	//FluChangeBackgroundWidget demo;
	//demo.show();

	//FluExampleTabWidget demo;
	//demo.show();

	//FluButtonExampleWidget demo;
	//demo.show();

	FluNavigationDemo demo;
	demo.show();

	return app.exec();
}