#include "Service.h"

void Service::modifySong(const int& id, const string& titlu, const int& rank)
{
	if (titlu == "")
		throw exception();
	this->r.modify(id, titlu, rank);
}

vector<Melodie> Service::getSongs()
{
	vector<Melodie> rez = this->r.getAll();
	for (unsigned int i = 0; i < rez.size() - 1; i++)
		for (unsigned int j = i + 1; j < rez.size(); j++)
			if (rez[i].getRank() > rez[j].getRank())
			{
				Melodie aux = rez[i];
				rez[i] = rez[j];
				rez[j] = aux;
			}
	return rez;
}

void Service::deleteSong(const int& id, const string& artist)
{
	Melodie m{ id, "frf", artist, 3 };
	this->r.del(m);
}

int Service::getNumberOfSongsByRank(const int& rank)
{
	return this->r.getNumberOfSongsByRank(rank);
}
