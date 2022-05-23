#include "Repository.h"
#include "Medicament.h"

using std::vector;
using std::string;
using std::ostream;

ostream& operator<<(ostream& out, const RepositoryException& ex)
{
	out << ex.eroare;
	return out;
}

bool Repo::exist(const Medicament& m) const
{
	try
	{
		find(m.getDenumire(), m.getProducator());
		return true;
	}
	catch (RepositoryException&)
	{
		return false;
	}
}

const Medicament& Repo::find(string denumire, string producator) const
{
	for (const auto& med : meds)
		if (med.getDenumire() == denumire && med.getProducator() == producator)
			return med;
	throw RepositoryException("Nu exista medicamentul cautat!");
}

int Repo::getPozitie(const Medicament& m) const
{
	int poz = -1;
	for (unsigned int i = 0; i < meds.size(); i++)
		if (meds[i].getDenumire() == m.getDenumire() && meds[i].getProducator() == m.getProducator())
			poz = i;
	return poz;
}

void Repo::add(const Medicament& m)
{
	if (exist(m))
	{
		throw RepositoryException("Medicamentul pe care doriti sa il adaugati exista deja!");
	}
	meds.push_back(m);
}

void Repo::modify(const Medicament& m, int camp)
{
	if (exist(m) == false)
		throw RepositoryException("Medicamentul pe care doriti sa il modificati nu exista!");

	int poz = getPozitie(m);

	if (camp == 1)
		meds[poz].setPret(m.getPret());

	if (camp == 2)
		meds[poz].setSubstantaActiva(m.getSubstantaActiva());

	if (camp == 3)
	{
		meds[poz].setPret(m.getPret());
		meds[poz].setSubstantaActiva(m.getSubstantaActiva());
	}
}

void Repo::del(const Medicament& m)
{
	if (exist(m) == false)
		throw(RepositoryException("Nu exista medicamentul pe care doriti sa il stergeti!"));

	int poz = getPozitie(m);
	meds.erase(meds.begin() + poz);
}

vector<Medicament> Repo::getMeds()
{
	return meds;
}