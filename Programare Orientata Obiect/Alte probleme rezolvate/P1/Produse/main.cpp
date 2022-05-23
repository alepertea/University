#include <QtWidgets/QApplication>
#include "Teste.h"
#include "ProdusGUI.h"
#include "Service.h"

int main(int argc, char* argv[])
{
    Test t;
    t.runTests();

    Valid v;
    Repo r{ "produse.txt" };
    Service s{ r, v };

    QApplication a(argc, argv);

    ProdusGUI gui{ s };
    gui.show();

    return a.exec();
}