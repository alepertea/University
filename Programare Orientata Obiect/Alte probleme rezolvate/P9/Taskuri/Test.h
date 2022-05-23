#pragma once
#include <assert.h>
#include "Task.h"
#include "Validator.h"
#include "Repository.h"
#include "Service.h"

class Test
{
private:
	void testEntity();
	void testValidator();
	void testAdaugare();
	void testCautare();
	void testModificare();
public:
	void runTests();
};