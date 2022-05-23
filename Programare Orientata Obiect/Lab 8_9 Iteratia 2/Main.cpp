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

		FileRepo r{"medicamente.txt", 0.4};
		Validator v{};
		Reteta ret{};
		Service s{ r, v, ret };
		ConsoleUI c{ s };

		c.start();
	}
	_CrtDumpMemoryLeaks();

	return 0;
}