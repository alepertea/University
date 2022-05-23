#pragma once
#include "Produs.h"
#include <vector>
#include <fstream>

class Repo
{
private:
	// lista de produse
	vector<Produs> produse;

	// numele fisierului
	string filename;

	// extrage datele din fisier
	void loadFromFile();

	// stocheaza datele in fisier
	void storeToFile();

	// verifica daca exista un produs in lista
	// returneaza true daca gaseste un produs cu acelasi id
	// returneaza fals altfel
	bool exist(const Produs& p);
public:
	Repo(const string& f) : filename{ f } { this->loadFromFile(); }

	// returneaza 1 daca produsul deja exista
	// il adauga altfel
	int add(const Produs& p);

	// returneaza lista de produse
	vector<Produs> getAll();

	// returneaza cate produse de un anumit tip exista in lista
	int getNumberOfProducts(const string& tip);
};