#include "Service.h"
#include "Medicament.h"
#include <functional>
#include <algorithm>

vector <Medicament> Service::getMeds() const
{
	return repo.getMeds();
}

void Service::addMed(const string& denumire, const string& producator, const double& pret, const int& substantaActiva)
{
	Medicament m{ denumire, producator, pret, substantaActiva };
	val.validate(m);
	repo.add(m);
}

Medicament Service::findMed(const string& denumire)
{
	Medicament gasit = repo.findMed(denumire);
	return gasit;
}

void Service::modifyMed(const string& denumire, const string& producator, const double& pret, const int& substantaActiva, const int& camp)
{
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
}

void Service::deleteMed(const string& denumire, const string& producator)
{
	const Medicament& m{ denumire, producator, 20, 1 };
	val.validate(m);
	repo.del(m);
}

vector<Medicament> Service::filterMeds(const double& pret, const int& substantaActiva, const int& criteriu) const
{
	vector<Medicament> rez;
	for (const auto& med : repo.getMeds())
	{
		if (criteriu == 1)
			if (med.getPret() < pret)
				rez.push_back(med);
		if (criteriu == 2)
			if (med.getSubstantaActiva() < substantaActiva)
				rez.push_back(med);
	}
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

void Service::addReteta(const string& denumire, const string& producator, const double& pret, const int& substantaActiva)
{
	Medicament m{ denumire, producator, pret, substantaActiva };
	val.validate(m);
	repo.addReteta(m);
}

void Service::clearAll()
{
	repo.clearAll();
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
		float pret = (float)rand();
		Medicament med{ denumire,producator,pret,substantaActiva };
		repo.addReteta(med);
	}
}

vector<pair<Medicament,int>> Service::afiseazaReteta()
{
	return repo.afiseazaReteta();
}

int Service::sizeReteta() const
{
	return repo.sizeReteta();
}