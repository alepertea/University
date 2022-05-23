#include "Medicament.h"
#include "Teste.h"
#include "Validator.h"
#include "Service.h"
#include "Repository.h"
#include <assert.h>
#include <sstream>

using namespace std;

void Test::testGetMedicament()
{
	Medicament m{ "Nurofen", "Marcel", 25.5, 3 };
	assert(m.getDenumire() == "Nurofen");
	assert(m.getPret() == 25.5);
	assert(m.getProducator() == "Marcel");
	assert(m.getSubstantaActiva() == 3);
}

void Test::testSetMedicament()
{
	Medicament m{ "Nurofen", "Marcel", 25.5, 3 };
	m.setPret(30);
	m.setSubstantaActiva(5);
	assert(m.getPret() == 30);
	assert(m.getSubstantaActiva() == 5);
}


void Test::testValidate()
{
	Validator v;
	Medicament valid{ "", "", 0, 0 };
	try
	{
		v.validate(valid);
	}
	catch (const ValidateException & erori)
	{
		std::stringstream sout;
		sout << erori;
		auto mesaj = sout.str();
		assert(mesaj.find("invalid") >= 0);
		assert(mesaj.find("invalida") >= 0);
	}
}

void Test::testAdaugare()
{
	Repo r{};
	Validator v{};
	Service s{ r, v };

	Lista<Medicament> allMeds = s.getMeds();
	// sir vid
	assert(allMeds.size() == 0);

	// adaug medicament inexistent
	try
	{
		s.addMed("Nurofen", "Marcel", 34, 2);
		assert(true);
	}
	catch (RepositoryException&)
	{
		assert(false);
	}

	// adaug medicament deja existent
	try
	{
		s.addMed("Nurofen", "Marcel", 100, 5);
		assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
}

void Test::testModificare()
{
	Repo r{};
	Validator v{};
	Service s{ r, v };

	// modificare pret
	s.addMed("Nurofen", "Marcel", 34, 2);
	s.modifyMed("Nurofen", "Marcel", 50, 5, 1);
	Lista<Medicament> allMeds = s.getMeds();
	assert(allMeds[0].getPret() == 50);
	assert(allMeds[0].getSubstantaActiva() == 2);

	// modificare cantitate de substanta activa
	s.addMed("Paracetamol", "Gigel", 23, 1);
	s.modifyMed("Paracetamol", "Gigel", 10, 4, 2);
	allMeds = s.getMeds();
	assert(allMeds[1].getPret() == 23);
	assert(allMeds[1].getSubstantaActiva() == 4);

	// modificare ambele campuri
	s.modifyMed("Nurofen", "Marcel", 65, 5, 3);
	allMeds = s.getMeds();
	assert(allMeds[0].getPret() == 65);
	assert(allMeds[0].getSubstantaActiva() == 5);

	// medicament inexistent
	try
	{
		s.modifyMed("Panadol", "Gigel", 10, 4, 2);
		assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	// camp invalid => medicamentul nu se modifica
	s.modifyMed("Nurofen", "Marcel", 10, 4, 10);
	allMeds = s.getMeds();
	assert(allMeds[0].getPret() == 65);
	assert(allMeds[0].getSubstantaActiva() == 5);
}

void Test::testCautare()
{
	Repo r{};
	Validator v{};
	Service s{ r, v };

	s.addMed("Nurofen", "Marcel", 43, 2);

	// cautare medicament existent
	try
	{
		s.findMed("Nurofen", "Marcel");
		assert(true);
	}
	catch (RepositoryException&)
	{
		assert(false);
	}

	// cautare medicament inexistent
	try
	{
		s.findMed("Panadol", "Gigi");
		assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
}

void Test::testStergere()
{
	Repo r{};
	Validator v{};
	Service s{ r, v };

	s.addMed("Nurofen", "Marcel", 43, 2);

	// stergere medicament inexistent
	try
	{
		s.deleteMed("Panadol", "Gigi");
		assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	// stergere medicament existent
	try
	{
		s.deleteMed("Nurofen", "Marcel");
		assert(true);
	}
	catch (RepositoryException&)
	{
		assert(false);
	}
}

void Test::testFiltrare()
{
	Repo r{};
	Validator v{};
	Service s{ r, v };

	s.addMed("Nurofen", "Marcel", 43, 2);

	Lista<Medicament> rez;

	// filtrare dupa pret
	rez = s.filterMeds(50, 3, 1);
	assert(rez.size() == 1);
	rez = s.filterMeds(20, 3, 1);
	assert(rez.size() == 0);

	// filtrare dupa cantitatea de substanta activa
	rez = s.filterMeds(40, 3, 2);
	assert(rez.size() == 1);
	rez = s.filterMeds(20, 1, 2);
	assert(rez.size() == 0);

	// criteriu invalid
	rez = s.filterMeds(32, 2, 5);
	assert(rez.size() == 0);
}

void Test::testSortari()
{
	Repo r{};
	Validator v{};
	Service s{ r, v };

	s.addMed("Panadol", "Gigi", 40, 9);
	s.addMed("Nurofen", "Marcel", 43, 2);

	// sortarea dupa denumire
	Lista<Medicament> rez = s.sortByDenumire();
	assert(rez[0].getDenumire() == "Nurofen");
	assert(rez[1].getDenumire() == "Panadol");

	// sortarea dupa producator
	rez = s.sortByProducator();
	assert(rez[0].getDenumire() == "Panadol");
	assert(rez[1].getDenumire() == "Nurofen");

	// sortarea dupa substanta activa + pret
	rez = s.sortBySubstantaSiPret();
	assert(rez[0].getDenumire() == "Panadol");
	assert(rez[1].getDenumire() == "Nurofen");

	s.addMed("ACC", "Idk", 30, 2);
	rez = s.sortBySubstantaSiPret();
	assert(rez[0].getDenumire() == "ACC");
}

void Test::runTests()
{
	testGetMedicament();
	testSetMedicament();
	testValidate();
	testAdaugare();
	testModificare();
	testCautare();
	testStergere();
	testFiltrare();
	testSortari();
}