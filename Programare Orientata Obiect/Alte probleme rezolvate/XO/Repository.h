#pragma once
#include <vector>
#include <fstream>
#include "Joc.h"

class Repo
{
private:
	vector<Joc> jocuri;

	string filename;
	void loadFromFile();
	void storeToFile();

	// verifica daca un joc exista in lista dupa id
	// returneaza true daca exista, fals altfel
	bool exist(const Joc& j);
public:
	Repo(const string& f) :filename{ f } { this->loadFromFile(); }
	
	// adauga un joc in lista
	void add(Joc j);

	void modify(const int& id, const int& dim, const string& tabla, const char& jucator, const string& stare);

	// returneaza lista de jocuri
	vector<Joc> getAll();
};