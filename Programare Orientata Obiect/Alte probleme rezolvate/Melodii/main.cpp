#include <QtWidgets/QApplication>
#include "Teste.h"
#include "Service.h"
#include "MelodieGUI.h"

int main(int argc, char* argv[])
{
    Test t;
    t.runTests();

    Repo r{ "melodii.txt" };
    Service s{ r };

    QApplication a(argc, argv);

    MelodieGUI gui{ s };
    gui.show();

    return a.exec();
}
