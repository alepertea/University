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

const Medicament& Service::findMed(const string& denumire, const string& producator)
{
	const Medicament& gasit = repo.find(denumire, producator);
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