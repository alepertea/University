#include "FileRepo.h"

void FileRepo::loadFromFile()
{
	ifstream fin(filename);
	if (!fin.is_open())
	{
		throw RepositoryException{ "Eroare la deschiderea fisierului:" };
	}

	while (!fin.eof())
	{
		string denumire, producator;
		fin >> denumire;
		fin >> producator;

		double pret;
		fin >> pret;

		int substantaActiva;
		fin >> substantaActiva;

		if (fin.eof())
		{
			break;
		}
		Medicament m{ denumire.c_str(), producator.c_str(), pret, substantaActiva };
		Repo::add(m);
	}

	fin.close();
}

void FileRepo::storeToFile()
{
	ofstream fout(filename);
	if (!fout.is_open())
	{
		throw RepositoryException{ "Eroare la deschiderea fisierului!" };
	}

	for (const auto& med : Repo::getMeds())
	{
		fout << med.getDenumire() << "\n";
		fout << med.getProducator() << "\n";
		fout << med.getPret() << "\n";
		fout << med.getSubstantaActiva() << '\n';
	}

	fout.close();
}

void FileRepo::add(const Medicament& m)
{
	Repo::add(m);
	storeToFile();
}

void FileRepo::modify(const Medicament& m, int camp)
{
	Repo::modify(m, camp);
	storeToFile();
}

void FileRepo::del(const Medicament& m)
{
	Repo::del(m);
	storeToFile();
}

void FileRepo::meds()
{
	storeToFile();
}