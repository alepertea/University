#include "Repository.h"
#include "Medicament.h"

ostream& operator<<(ostream& out, const RepositoryException& ex)
{
	out << ex.eroare;
	return out;
}

Medicament Repo::findMed(string denumire) const
{
	auto it = meds.find(denumire);
	if(it == meds.end())
		throw RepositoryException("Nu exista medicamentul cautat!");
	return it->second;
}

bool Repo::exist(const Medicament& m) const
{
	try
	{
		Medicament med = findMed(m.getDenumire());
		return true;
	}
	catch (RepositoryException&)
	{
		return false;
	}
}

auto Repo::getPozitie(const Medicament& m) const
{
	return meds.find(m.getDenumire());
}

int Repo::getPozitieReteta(const Medicament& m) const
{
	for (unsigned int i = 0; i < reteta.size(); i++)
	{
		if (m.getDenumire() == reteta[i].first.getDenumire() && m.getProducator() == reteta[i].first.getProducator())
			return i;
	}
	return -1;
}

void Repo::add(const Medicament& m)
{
	if (exist(m))
	{
		throw RepositoryException("Medicamentul pe care doriti sa il adaugati exista deja!");
	}
	meds.insert(pair<string, Medicament>(m.getDenumire(), m));
}

void Repo::modify(const Medicament& m, int camp)
{
	if (exist(m) == false)
		throw RepositoryException("Medicamentul pe care doriti sa il modificati nu exista!");

	Medicament med = findMed(m.getDenumire());
	if (camp == 1)
	{
		med.setPret(m.getPret());
		meds.insert_or_assign(m.getDenumire(), med);
	}

	if (camp == 2)
	{
		med.setSubstantaActiva(m.getSubstantaActiva());
		meds.insert_or_assign(m.getDenumire(), med);

	}

	if (camp == 3)
	{
		med.setPret(m.getPret());
		meds.insert_or_assign(m.getDenumire(), med);

		med.setSubstantaActiva(m.getSubstantaActiva());
		meds.insert_or_assign(m.getDenumire(), med);
	}
}

void Repo::del(const Medicament& m)
{
	if (exist(m) == false)
		throw(RepositoryException("Nu exista medicamentul pe care doriti sa il stergeti!"));

	auto it = getPozitie(m);
	meds.erase(it);
}

vector<Medicament> Repo::getMeds()
{
	vector<Medicament> vect;
	vect.reserve(meds.size());
	std::transform(meds.begin(), meds.end(), back_inserter(vect), [](std::pair<std::string, Medicament> const& pair)
		{
			return pair.second;
		});
	return vect;
}

void Repo::addReteta(const Medicament& m)
{
	int poz = getPozitieReteta(m);
	if (poz == -1)
		reteta.push_back(pair<Medicament, int>(m, 1));
	else
		reteta[poz].second++;
}

void Repo::clearAll()
{
	reteta.clear();
}

vector<pair<Medicament, int>> Repo::afiseazaReteta()
{
	return reteta;
}

int Repo::sizeReteta() const
{
	int count = 0;
	for (const auto& med : reteta)
	{
		count += med.second;
	}
	return count;
}