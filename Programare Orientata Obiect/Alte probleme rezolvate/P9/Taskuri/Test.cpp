#include "Test.h"

void Test::testEntity()
{
	vector<string> p;
	p.push_back("Ana"); p.push_back("Ion");
	Task t{ 1, "idk", p, "closed" };
	assert(t.getID() == 1);
	assert(t.getDescriere() == "idk");
	assert(t.getStare() == "closed");
	assert(t.getProgramatori() == p);

	t.setStare("open");
	assert(t.getStare() == "open");
}

void Test::testValidator()
{
	vector<string> p; p.push_back("Ana");
	Task valid{ 1, "idk", p, "open" };

	Valid v;
	// testam pe un task valid -> nu ar trebui sa arunce exceptie
	try
	{
		v.validate(valid);
		assert(true);
	}
	catch (ValidException&)
	{
		assert(false);
	}

	// testam stare invalida -> ar trebui sa arunce exceptie
	Task stareInvalida{ 1, "idk", p, "done" };
	try
	{
		v.validate(stareInvalida);
		assert(false);
	}
	catch (ValidException& e)
	{
		assert(e.getMessage() == "Stare invalida");
	}

	// testam descriere invalida -> ar trebui sa arunce exceptie
	Task descriereInvalida{ 1, "", p, "open" };
	try
	{
		v.validate(descriereInvalida);
		assert(false);
	}
	catch (ValidException& e)
	{
		assert(e.getMessage() == "Descriere invalida");
	}

	// testam pentru numar de programatori mai mare -> ar trebui sa arunce exceptie
	p.push_back("Ion");
	p.push_back("Gigel");
	p.push_back("Petra");
	p.push_back("Marcu");
	Task progInvalid{ 1, "idk", p, "closed" };
	try
	{
		v.validate(progInvalid);
		assert(false);
	}
	catch (ValidException& e)
	{
		assert(e.getMessage() == "Numar de programatori invalid");
	}
}

void Test::testAdaugare()
{
	Repo r{ "test.txt" };

	// adaugam un task inexistent -> nu ar trebui sa arunce exceptie
	vector<string> p; p.push_back("Ana");
	Task t{ 1, "idk", p, "inprogress" };
	try
	{
		r.add(t);
		assert(r.getAll().size() == 1);
	}
	catch (RepoException&)
	{
		assert(false);
	}

	// sterg datele din fisier ca sa nu ma incurc la celelalte teste
	ofstream f("test.txt");
	f.clear();
	f.close();
}

void Test::testCautare()
{
	Repo r{ "test.txt" };
	vector<string> p; p.push_back("Ana");
	Task t1{ 1, "idk", p, "closed" };
	r.add(t1);
	assert(r.getTasksByProg("Ana").size() == 1);
	assert(r.getTasksByProg("Ionel").size() == 0);

	assert(r.getTasksByState("closed").size() == 1);
	assert(r.getTasksByState("open").size() == 0);

	ofstream f("test.txt");
	f.clear();
	f.close();
}

void Test::testModificare()
{
	Repo r{ "test.txt" };
	Task t{ 1, "idk", {"Ana"}, "open" };
	r.add(t);
	r.modify(1, "closed");
	assert(r.getAll()[0].getStare() == "closed");

	ofstream f("test.txt");
	f.clear();
	f.close();
}

void Test::runTests()
{
	this->testEntity();
	this->testValidator();
	this->testAdaugare();
	this->testCautare();
	this->testModificare();
}
