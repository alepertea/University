#include "Service.h"
#include "Medicament.h"
#include <functional>
#include <algorithm>

Lista<Medicament> Service::getMeds() const
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

Lista<Medicament> Service::filterMeds(const double& pret, const int& substantaActiva, const int& criteriu) const
{
	Lista<Medicament> rez;
	for (const auto& med : repo.getMeds())
	{
		if (criteriu == 1)
			if (med.getPret() < pret)
				rez.adaugaSfarsit(med);
		if (criteriu == 2)
			if (med.getSubstantaActiva() < substantaActiva)
				rez.adaugaSfarsit(med);
	}
	return rez;
}

Lista<Medicament> Service::sortByDenumire()
{
	Lista<Medicament> rez = getMeds();
	for (unsigned int i = 0; i < rez.size() - 1; i++)
		for (unsigned int j = i + 1; j < rez.size(); j++)
			if (rez[i].getDenumire() > rez[j].getDenumire())
			{
				Medicament aux = rez[i];
				rez[i] = rez[j];
				rez[j] = aux;
			}
	return rez;
}

Lista<Medicament> Service::sortByProducator()
{
	Lista<Medicament> rez = getMeds();
	for (unsigned int i = 0; i < rez.size() - 1; i++)
		for (unsigned int j = i + 1; j < rez.size(); j++)
			if (rez[i].getProducator() > rez[j].getProducator())
			{
				Medicament aux = rez[i];
				rez[i] = rez[j];
				rez[j] = aux;
			}
	return rez;
}

Lista<Medicament> Service::sortBySubstantaSiPret()
{
	Lista<Medicament> rez = getMeds();
	for (unsigned int i = 0; i < rez.size() - 1; i++)
		for (unsigned int j = i + 1; j < rez.size(); j++)
			if (rez[i].getPret() > rez[j].getPret())
			{
				Medicament aux = rez[i];
				rez[i] = rez[j];
				rez[j] = aux;
			}
			else
				if (rez[i].getPret() == rez[j].getPret())
					if (rez[i].getSubstantaActiva() > rez[j].getSubstantaActiva())
					{
						Medicament aux = rez[i];
						rez[i] = rez[j];
						rez[j] = aux;
					}
	return rez;
}