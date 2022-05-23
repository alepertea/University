#pragma once
#include "Melodie.h"
#include <vector>
#include <fstream>

class RepoException
{
private:
	string msg;
public:
	RepoException(const string& msg) :msg{ msg } {}

	string getMessage() const;
};

class Repo
{
private:
	// lista melodiilor
	vector<Melodie> songs;

	// numele fisierului
	string filename;

	// extrage datele din fisier
	void loadFromFile();

	// stocheaza datele in fisier
	void storeToFile();

	// verifica daca exista o melodie cu acelasi id
	// returneaza true daca exista, fals altfel
	bool exist(const Melodie& m);

	// returneaza pozitia unei melodii in lista
	int getPozitie(const Melodie& m);

public:
	Repo(const string& f) :filename{ f } { this->loadFromFile(); }

	// adauga o melodie in lista
	void add(const Melodie& m);

	// modifica atat titlul cat si rank-ul unei melodii
	void modify(const int& id, const string& titlu, const int& rank);

	// returneaza lista de melodii
	vector<Melodie> getAll();

	// sterge o melodie din lista
	void del(const Melodie& m);
	
	int getNumberOfSongsByRank(const int& rank);
};