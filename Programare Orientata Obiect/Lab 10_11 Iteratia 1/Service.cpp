#include "Service.h"

vector <Medicament> Service::getMeds() const
{
	return repo.getMeds();
}

void Service::addMed(const string& denumire, const string& producator, const double& pret, const int& substantaActiva)
{	
	double probabilitate = (rand() % 100) * 1.0 / 100;
	if (probabilitate < repo.getErrorPercentage())
	{
		throw RepositoryException("Ups");
	}
	
	Medicament m{ denumire, producator, pret, substantaActiva };
	val.validate(m);
	repo.add(m);
	undoActions.push_back(make_unique<UndoAdauga>(repo, m));
}

Medicament Service::findMed(const string& denumire)
{
	Medicament gasit = repo.findMed(denumire);
	return gasit;
}

void Service::modifyMed(const string& denumire, const string& producator, const double& pret, const int& substantaActiva, const int& camp)
{
	double probabilitate = (rand() % 100) * 1.0 / 100;
	if (probabilitate < repo.getErrorPercentage())
	{
		throw RepositoryException("Ups");
	}

	try
	{
		Medicament medInitial = repo.findMed(denumire);

		// modificarea pretului
		if (camp == 1)
		{
			const Medicament& m{ denumire, producator, pret, 2 };
			val.validate(m);
			repo.modify(m, camp);
		}

		// modificarea cantitatii de substanta activa
		if (camp == 2)
		{
			const Medicament& m{ denumire, producator, 100, substantaActiva };
			val.validate(m);
			repo.modify(m, camp);
		}

		// modificarea ambelor campuri
		if (camp == 3)
		{
			const Medicament& m{ denumire, producator, pret, substantaActiva };
			val.validate(m);
			repo.modify(m, camp);
		}

		Medicament medModificat = repo.findMed(denumire);

		undoActions.push_back(make_unique<UndoModifica>(repo, medInitial, medModificat));
	}
	catch (RepositoryException&)
	{
		cout << "Medicamentul nu exista! \n";
	}
}

void Service::deleteMed(const string& denumire, const string& producator)
{
	double probabilitate = (rand() % 100) * 1.0 / 100;
	if (probabilitate < repo.getErrorPercentage())
	{
		throw RepositoryException("Ups");
	}

	const Medicament& m{ denumire, producator, 20, 1 };
	val.validate(m);
	repo.del(m);
	undoActions.push_back(make_unique<UndoSterge>(repo, m));
}

vector<Medicament> Service::filterMeds(const double& pret, const int& substantaActiva, const int& criteriu) const
{
	vector<Medicament> rez;
	vector<Medicament> meds = repo.getMeds();
	if (criteriu == 1)
		copy_if(meds.begin(), meds.end(), back_inserter(rez), [=](const Medicament& m) {return m.getPret() < pret; });
	if (criteriu == 2)
		copy_if(meds.begin(), meds.end(), back_inserter(rez), [=](const Medicament& m) {return m.getSubstantaActiva() < substantaActiva; });
	return rez;
}

vector<Medicament> Service::sortByDenumire()
{
	auto allMeds = repo.getMeds();
	std::sort(allMeds.begin(), allMeds.end(), cmpDenumire);
	return allMeds;
}

vector<Medicament> Service::sortByProducator()
{
	auto allMeds = repo.getMeds();
	std::sort(allMeds.begin(), allMeds.end(), cmpProducator);
	return allMeds;
}

vector<Medicament> Service::sortBySubstantaSiPret()
{
	auto allMeds = repo.getMeds();
	std::sort(allMeds.begin(), allMeds.end(), cmpSubstantaSiPret);
	return allMeds;
}

double Service::stats() const
{
	double suma = 0;
	auto vect = getMeds();
	vector<double> rez;

	for (auto it : vect)
		rez.push_back(it.getPret());

	return accumulate(rez.begin(), rez.end(), suma);
}

// Reteta:

void Service::addReteta(const string& denumire, const string& producator, const double& pret, const int& substantaActiva)
{
	Medicament m{ denumire, producator, pret, substantaActiva };
	val.validate(m);
	ret.addReteta(m);
	undoActions.push_back(make_unique<UndoAddReteta>(ret, m));
}

void Service::clearAll()
{
	ret.clearAll();
}

string Service::randomString()
{
	std::string str("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device rand;
	std::mt19937 generator(rand());

	std::shuffle(str.begin(), str.end(), generator);

	return str.substr(0, 10);
}

void Service::random(int nrMeds)
{
	for (int i = 1; i <= nrMeds; i++)
	{
		string denumire = randomString();
		string producator = randomString();
		int substantaActiva = rand();
		double pret = (double)rand();
		addReteta(denumire, producator, pret, substantaActiva);
	}
}

vector<Medicament> Service::getReteta()
{
	return ret.getReteta();
}

size_t Service::sizeReteta() const
{
	return ret.sizeReteta();
}

// Export:

void Service::exportCSV(const string& filename) const
{
	exportToCSV(filename, ret.getReteta());
}

void Service::exportHTML(const string& filename) const
{
	exportToHTML(filename, ret.getReteta());
}

// Undo:

void Service::undo()
{
	if (undoActions.empty())
	{
		throw RepositoryException{ "Nu mai exista operatii pentru undo!" };
	}

	undoActions.back()->doUndo();
	undoActions.pop_back();
}