#include <QtWidgets/QApplication>
#include "Test.h"
#include "Service.h"
#include "TaskGUI.h"
#include "OpenGUI.h"
#include "ClosedGUI.h"
#include "InProgressGUI.h"

int main(int argc, char* argv[])
{
    Test t;
    t.runTests();

    Repo r{ "task.txt" };
    Valid v;
    Service s{ r, v };

    QApplication a(argc, argv);

    TaskGUI gui{ s };
    gui.show();

    OpenGUI guiO{ s, gui };
    guiO.show();

    InProgressGUI guiP{ s, gui };
    guiP.show();

    ClosedGUI guiC{ s, gui };
    guiC.show();

    return a.exec();
}
