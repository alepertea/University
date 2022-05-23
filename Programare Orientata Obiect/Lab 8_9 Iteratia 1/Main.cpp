#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "ui.h"
#include "Teste.h"

int main()
{
	{
		Test t{};
		t.runTests();

		Repo r{};
		Validator v{};
		Service s{ r, v };
		ConsoleUI c{ s };

		c.start();
	}
	_CrtDumpMemoryLeaks();

	return 0;
}