#include "Teste.h"

void Test::testEntity()
{
	Produs p{ 1, "ciocolata", "dulciuri", 9.99 };
	assert(p.getID() == 1);
	assert(p.getNume() == "ciocolata");
	assert(p.getTip() == "dulciuri");
	assert(p.getPret() == 9.99);
	assert(p.getNumarVocale() == 5);
}

void Test::testValidari()
{
	Valid v;

	// testam produs valid
	Produs valid{ 1, "ciocolata", "dulciuri", 2 };
	assert(v.validate(valid) == 0);

	// testam nume invalid
	Produs numeInvalid{ 1, "", "dulciuri", 2 };
	assert(v.validate(numeInvalid) == 2);

	// testam pret invalid
	Produs pretInvalid{ 1, "ciocolata", "dulciuri", 221 };
	assert(v.validate(pretInvalid) == 3);

	// testam nume si pret invalide
	Produs ambeleInvalide{ 1, "", "dulciuri", -2 };
	assert(v.validate(ambeleInvalide) == 6);
}

void Test::testAdaugare()
{
	Repo r{ "test.txt" };
	Produs p{ 1, "ciocolata", "dulciuri", 2 };
	assert(r.add(p) == 0);
	assert(r.add(p) == 1);

	ofstream f("test.txt");
	f.clear();
	f.close();
}

void Test::testSortare()
{
	Valid v;
	Repo r{ "test.txt" };
	Service s{ r,v };

	Produs p1{ 2, "cioco", "dulciuri", 20 };
	r.add(p1);
	Produs p2{ 7, "mar", "fructe", 10 };
	r.add(p2);

	vector<Produs> rez = r.getAll();
	assert(rez[0].getID() == 2);

	rez = s.sortByPrice();
	assert(rez[0].getID() == 7);

	ofstream f("test.txt");
	f.clear();
	f.close();
}

void Test::runTests()
{
	this->testEntity();
	this->testValidari();
	this->testAdaugare();
	this->testSortare();
}