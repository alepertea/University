#pragma once
#include "Service.h"
#include <assert.h>

class Test
{
private:
	void testEntity();
	void testModificare();
public:
	Test() = default;
	void runTests();
};