#include "Teste.h"

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
	catch (const ValidateException& erori)
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

	vector<Medicament> allMeds = r.getMeds();
	// sir vid
	assert(allMeds.size() == 0);

	Medicament bun{ "Nurofen", "Marcel", 34, 2 };
	// adaug medicament inexistent
	try
	{
		r.add(bun);
		assert(true);
	}
	catch (RepositoryException&)
	{
		assert(false);
	}

	// adaug medicament deja existent
	try
	{
		Medicament existent{ "Nurofen", "Marcel", 100, 5 };
		r.add(existent);
		assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
}

void Test::testModificare()
{
	Repo r;

	// modificare pret
	Medicament pret1{ "Nurofen", "Marcel", 34, 2 };
	Medicament pret2{ "Nurofen", "Marcel", 50, 1 };
	r.add(pret1);
	r.modify(pret2, 1);
	vector<Medicament> allMeds = r.getMeds();
	assert(allMeds[0].getPret() == 50);
	assert(allMeds[0].getSubstantaActiva() == 2);

	// modificare cantitate de substanta activa
	Medicament subst1{ "Paracetamol", "Gigel", 23, 1 };
	Medicament subst2{ "Paracetamol", "Gigel", 50, 2 };
	r.add(subst1);
	r.modify(subst2, 2);
	allMeds = r.getMeds();
	assert(allMeds[1].getPret() == 23);
	assert(allMeds[1].getSubstantaActiva() == 2);

	// modificare ambele campuri
	r.modify(pret1, 3);
	allMeds = r.getMeds();
	assert(allMeds[0].getPret() == 34);
	assert(allMeds[0].getSubstantaActiva() == 2);

	// medicament inexistent
	Medicament inexistent{ "Panadol", "Gigel", 10, 4 };
	try
	{
		r.modify(inexistent, 2);
		assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	// camp invalid => medicamentul nu se modifica
	Medicament campInvalid{ "Nurofen", "Marcel", 10, 4 };
	r.modify(campInvalid, 10);
	allMeds = r.getMeds();
	assert(allMeds[0].getPret() == 34);
	assert(allMeds[0].getSubstantaActiva() == 2);
}

void Test::testCautare()
{
	Repo r{};

	Medicament med{ "Nurofen", "Marcel", 43, 2 };
	r.add(med);

	// cautare medicament existent
	try
	{
		Medicament gasit = r.findMed("Nurofen");
		assert(true);
	}
	catch (RepositoryException&)
	{
		assert(false);
	}

	// cautare medicament inexistent
	try
	{
		Medicament inexistent = r.findMed("Panadol");
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

	Medicament med{ "Nurofen", "Marcel", 43, 2 };
	r.add(med);

	// stergere medicament inexistent
	try
	{
		Medicament inexistent{ "Panadol", "Gigi", 22, 1 };
		r.del(inexistent);
		assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	// stergere medicament existent
	try
	{
		r.del(med);
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
	Reteta ret{};
	Validator v{};
	Service s{ r, v, ret };

	Medicament med{ "Nurofen", "Marcel", 43, 2 };
	r.add(med);

	vector<Medicament> rez;

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
	Reteta ret{};
	Service s{ r, v, ret };

	Medicament m1{ "Panadol", "Gigi", 40, 9 };
	Medicament m2{ "Nurofen", "Marcel", 43, 2 };
	r.add(m1);
	r.add(m2);

	// sortarea dupa denumire
	vector<Medicament> rez = s.sortByDenumire();
	assert(rez[0].getDenumire() == "Nurofen");
	assert(rez[1].getDenumire() == "Panadol");

	// sortarea dupa producator
	rez = s.sortByProducator();
	assert(rez[0].getDenumire() == "Panadol");
	assert(rez[1].getDenumire() == "Nurofen");

	// sortarea dupa substanta activa + pret
	rez = s.sortBySubstantaSiPret();
	assert(rez[0].getDenumire() == "Nurofen");
	assert(rez[1].getDenumire() == "Panadol");

	Medicament m3{ "ACC", "Idk", 30, 2 };
	s.addMed("ACC", "Idk", 30, 2);
	rez = s.sortBySubstantaSiPret();
	assert(rez[0].getDenumire() == "ACC");
}

void Test::testReteta()
{
	Repo r{};
	Validator v{};
	Reteta ret{};
	Service s{ r, v, ret };

	// adaugare un medicament
	s.addReteta("Nurofen", "Marcel", 32, 2);
	s.addReteta("Nurofen", "Marcel", 32, 2);
	auto reteta = s.getReteta();
	assert(s.sizeReteta() == 2);

	// golire reteta
	s.clearAll();
	assert(s.sizeReteta() == 0);

	// adaugare medicamente random
	s.random(4);
	assert(s.sizeReteta() == 4);

	s.clearAll();
}

void Test::testUndo()
{
	Repo r{};
	Validator v{};
	Reteta ret{};
	Service s{ r, v, ret };

	// Nu exista operatii, deci nu se poate efectua undo
	try
	{
		s.undo();
		assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	// Undo adaugare
	s.addMed("Nurofen", "Marcel", 34, 2);
	vector<Medicament> allMeds = r.getMeds();
	assert(allMeds.size() == 1);
	s.undo();
	allMeds = r.getMeds();
	assert(allMeds.size() == 0);

	// Undo stergere
	s.addMed("Nurofen", "Marcel", 34, 2);
	s.deleteMed("Nurofen", "Marcel");
	allMeds = r.getMeds();
	assert(allMeds.size() == 0);
	s.undo();
	allMeds = r.getMeds();
	assert(allMeds.size() == 1);
	s.deleteMed("Nurofen", "Marcel");

	// Undo modificare - pret
	Medicament med{ "Nurofen", "Marcel", 34,2 };
	s.addMed("Nurofen", "Marcel", 34, 2);
	s.modifyMed("Nurofen", "Marcel", 50, 1, 1);
	allMeds = r.getMeds();
	assert(allMeds[0].getPret() == 50);
	s.undo();
	allMeds = r.getMeds();
	assert(allMeds[0].getPret() == 34);

	// Undo la adaugarea in reteta
	s.addReteta("Nurofen", "Marcel", 43, 2);
	assert(ret.getReteta().size() == 1);
	s.undo();
	assert(ret.getReteta().size() == 0);
}

void Test::testStatistica()
{
	Repo r{};
	Validator v{};
	Reteta ret{};
	Service s{ r, v, ret };

	double suma = s.stats();
	assert(suma == 0);

	Medicament med{ "Nurofen", "Marcel", 23, 2 };
	r.add(med);
	suma = s.stats();
	assert(suma == 23);
}

void Test::testFileRepo()
{
	FileRepo repo{ "test.txt", 0.2 };

	// Adaugare medicament
	Medicament med{ "Nurofen", "Marcel", 12, 3 };
	repo.add(med);

	// Cautare medicament existent
	auto gasit = repo.findMed("Nurofen");
	assert(gasit.getPret() == 12);

	// Cautare medicament inexistent
	try
	{
		repo.findMed("Panadol");
		assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	// Stergere medicament existent
	repo.del(med);
	assert(repo.getMeds().size() == 0);

	// Stergere medicament inexistent
	Medicament inexistent{ "Panadol", "Gigi", 34, 2 };
	try
	{
		repo.del(inexistent);
		assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	// Nu se poate crea fisierul
	try
	{
		FileRepo repoNuBun{ "te/st.txt", 0.3 };
		assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
}

string randomString()
{
	string str("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	random_device rand;
	mt19937 generator(rand());

	shuffle(str.begin(), str.end(), generator);

	return str.substr(0, 10);
}

void Test::testErrorPercentage()
{
	FileRepo r{ "test.txt", 0.5 };
	Validator v{};
	Reteta ret;
	Service s{ r, v, ret };

	for (int i = 0; i < 100; i++)
	{
		try
		{
			string denumire = randomString();
			string producator = randomString();
			double pret = (double)rand();
			int substantaActiva = rand();
			s.addMed(denumire, producator, pret, substantaActiva);
			cout << "Yay!!!\n";
		}
		catch (RepositoryException&)
		{
			cout << "Ups\n";
		}
	}
}

void Test::testDTO()
{
	DTO dto{ 4, 2 };
	assert(dto.getSubstantaActiva() == 4);
	assert(dto.getNrMedicamente() == 2);
	dto.setNrMedicamente(5);
	assert(dto.getNrMedicamente() == 5);
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
	testReteta();
	testUndo();
	testStatistica();
	testFileRepo();
	testErrorPercentage();
	testDTO();

	ofstream f("test.txt");
	f.clear();
	f.close();
}