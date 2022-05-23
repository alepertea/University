#include <QtWidgets/QApplication>
#include "Teste.h"
#include "Service.h"
#include "JocGUI.h"

int main(int argc, char *argv[])
{
    Test t;
    t.runTests();

    Valid v;
    Repo r{ "jocuri.txt" };
    Service s{ r, v };

    QApplication a(argc, argv);

    JocGUI gui{ s };
    gui.show();

    return a.exec();
}
