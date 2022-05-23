#pragma once
#include "Melodie.h"
#include "Repository.h"

class Service
{
private:
	Repo& r;
public:
	Service(Repo& r) :r{ r } {}

	// modifica o melodie
	void modifySong(const int& id, const string& titlu, const int& rank);

	// returneaza lista de melodii din repo
	// lista va fi ordonata crescator dupa rank
	vector<Melodie> getSongs();

	void deleteSong(const int& id, const string& artist);

	int getNumberOfSongsByRank(const int& rank);
};