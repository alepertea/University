#include <QtWidgets/QApplication>
//#include <QtWidgets/qlabel.h>
//#include <QtWidgets/qpushbutton.h>
//#include <QtWidgets/qboxlayout.h>
//#include <QtWidgets/qformlayout.h>
//#include <QtWidgets/qlineedit.h>
//#include <QtWidgets/qlistwidget.h>
#include "Teste.h"
#include "Service.h"
#include "ProductGUI.h"

int main(int argc, char *argv[])
{
	//Test t;
	//t.runTests();

	FileRepo r{"medicamente.txt", 0.3};
	Validator v;
	Reteta ret;
	Service s{ r, v, ret };

	QApplication a(argc, argv);
	ProductGUI gui{ s };
	gui.show();
	
	return a.exec();
}