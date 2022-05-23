#include "Repository.h"

ostream& operator<<(ostream& out, const RepositoryException& ex)
{
	out << ex.eroare;
	return out;
}

Repo::Repo(double errorPercentage)
{
	error = errorPercentage;
}

double Repo::getErrorPercentage() const
{
	return error;
}

Medicament Repo::findMed(string denumire) const
{
	auto it = meds.find(denumire);
	if (it == meds.end())
		throw RepositoryException("Nu exista medicamentul cautat!");
	else
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
	std::transform(meds.begin(), meds.end(), back_inserter(vect), [](pair<string, Medicament> const& pair) {	return pair.second;	});
	return vect;
}

// Reteta:

void Reteta::addReteta(const Medicament& m)
{
	reteta.push_back(m);
}

void Reteta::stergeInReteta(const Medicament& m)
{
	int poz = getPozitieReteta(m);
	if (poz == -1)
	{
		throw RepositoryException{ "Medicamentul nu exista!" };
	}
	reteta.erase(reteta.begin() + poz);
}

void Reteta::clearAll()
{
	reteta.clear();
}

vector<Medicament> Reteta::getReteta()
{
	return reteta;
}

Medicament Reteta::findMed(const string& denumire)
{
	Medicament med{ denumire, "Producator", 12, 1 };
	int poz = getPozitieReteta(med);
	if (poz == -1)
		throw RepositoryException("Nu exista medicamentul dorit!");
	return reteta[poz];
}

size_t Reteta::sizeReteta() const
{
	return reteta.size();
}

int Reteta::getPozitieReteta(const Medicament& m) const
{
	int poz = 0;
	for (const auto& med : reteta)
	{
		if (m.getDenumire() == med.getDenumire())
			return poz;
		poz++;
	}
	return -1;
}