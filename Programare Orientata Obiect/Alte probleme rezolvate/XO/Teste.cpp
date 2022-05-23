#include "Teste.h"

void Test::testEntity()
{
	Joc j{ 1, 3, "XOX-XOX-X", 'O', "InDerulare" };

	// testam gettere
	assert(j.getID() == 1);
	assert(j.getDim() == 3);
	assert(j.getTabla() == "XOX-XOX-X");
	assert(j.getJucator() == 'O');
	assert(j.getStare() == "InDerulare");

	// testam settere
	j.setID(2);
	assert(j.getID() == 2);
	j.setJucator('X');
	assert(j.getJucator() == 'X');
	j.setStare("Terminat");
	assert(j.getStare() == "Terminat");
}

void Test::testValidator()
{
	Valid v;

	// testam joc valid -> nu ar trebui sa arunce exceptie
	Joc valid{ 1, 3, "XOX-XOX-X", 'O', "InDerulare" };
	try
	{
		v.validate(valid);
		assert(true);
	}
	catch (ValidException&)
	{
		assert(false);
	}

	// testam dimensiune invalida
	Joc dimInvalida{ 1, 13, "XOX-XOX-X", 'O', "InDerulare" };
	try
	{
		v.validate(dimInvalida);
		assert(false);
	}
	catch (ValidException& e)
	{
		assert(e.getMessage() == "Dimensiune invalida");
	}

	// testam dimensiune tabla invalida
	Joc tablaInvalida{ 1, 3, "XOX-XOX-XOXOXOX", 'O', "InDerulare" };
	try
	{
		v.validate(tablaInvalida);
		assert(false);
	}
	catch (ValidException& e)
	{
		assert(e.getMessage() == "Dimensiune tabla invalida");
	}

	// testam tabla invalida
	Joc carInvalid{ 1, 3, "XOX-YOX-X", 'O', "InDerulare" };
	try
	{
		v.validate(carInvalid);
		assert(false);
	}
	catch (ValidException& e)
	{
		assert(e.getMessage() == "Tabla invalida");
	}

	// testam jucator invalid
	Joc jucatorInvalid{ 1, 3, "XOX-XOX-X", 'Y', "InDerulare" };
	try
	{
		v.validate(jucatorInvalid);
		assert(false);
	}
	catch (ValidException& e)
	{
		assert(e.getMessage() == "Jucator invalid");
	}

	// testam stare invalida
	Joc stareInvalida{ 1, 3, "XOX-XOX-X", 'O', "Nuj" };
	try
	{
		v.validate(stareInvalida);
		assert(false);
	}
	catch (ValidException& e)
	{
		assert(e.getMessage() == "Stare invalida");
	}
}

void Test::testModificare()
{
	Valid v;
	Repo r{ "test.txt" };
	Service s{ r, v };

	s.add(1, 3, "XOXOXOXOX", 'O', "Terminat");
	assert(s.getAll().size() == 1);

	s.modify(1, 3, "XOXOXOXOX", 'X', "Neinceput");
	assert(s.getAll()[0].getJucator() == 'X');
	assert(s.getAll()[0].getStare() == "Neinceput");

	ofstream f("test.txt");
	f.clear();
	f.close();
}

void Test::runTests()
{
	this->testEntity();
	this->testValidator();
	this->testModificare();
}
