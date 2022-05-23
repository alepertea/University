#pragma once
#include "Produs.h"
#include "Validator.h"
#include "Repository.h"
#include "Service.h"
#include <assert.h>

class Test
{
private:
	void testEntity();
	void testValidari();
	void testAdaugare();
	void testSortare();
public:
	Test() = default;
	void runTests();
};