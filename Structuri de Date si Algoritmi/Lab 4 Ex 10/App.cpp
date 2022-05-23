#include "TestExtins.h"
#include "TestScurt.h"
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

int main() 
{
	{
		testAll();
		testAllExtins();
		cout << "That's all!" << endl;
	}
	_CrtDumpMemoryLeaks();
}