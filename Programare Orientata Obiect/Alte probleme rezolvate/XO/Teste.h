#pragma once
#include <assert.h>
#include "Joc.h"
#include "Validator.h"
#include "Service.h"

class Test
{
private:
	void testEntity();
	void testValidator();
	void testModificare();

public:
	Test() = default;

	void runTests();
};