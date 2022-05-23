#include <QtWidgets/QApplication>
#include "Teste.h"
#include "Service.h"
#include "ProductGUI.h"

int main(int argc, char* argv[])
{
	Test t;
	t.runTests();

	Repo r;
	Validator v;
	Reteta ret;
	Service s{ r, v, ret };

	QApplication a(argc, argv);
	ProductGUI gui{ s };
	gui.show();

	return a.exec();
}