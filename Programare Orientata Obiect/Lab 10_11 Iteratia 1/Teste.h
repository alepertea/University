#pragma once
#include "Medicament.h"
#include "Teste.h"
#include "Validator.h"
#include "Service.h"
#include "FileRepo.h"
#include "Undo.h"
#include <assert.h>
#include <fstream>
#include <iostream>

using namespace std;

class Test
{
private:
	void testGetMedicament();

	void testSetMedicament();

	void testValidate();

	void testAdaugare();

	void testModificare();

	void testCautare();

	void testStergere();

	void testFiltrare();

	void testSortari();

	void testReteta();

	void testStatistica();

	void testUndo();

	void testFileRepo();

	void testErrorPercentage();
public:
	void runTests();
};