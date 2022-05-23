#pragma once
#include "Medicament.h"
#include <vector>
#include <string>
#include <ostream>
#include <map>
#include <algorithm>

/*
using std::vector;
using std::string;
using std::ostream;
using std::map;
using std::pair;
*/
using namespace std;

class RepositoryException
{
private:
	string eroare;
public:
	RepositoryException(string e) : eroare{ e } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const RepositoryException& ex);
};

ostream& operator<<(ostream& out, const RepositoryException& ex);

class Repo
{
private:
	/* Dictionar de medicamente */
	map<string, Medicament> meds;

	/* Vector de medicamente pentru reteta */
	vector<pair<Medicament, int>> reteta;

	/*
		Returneaza pozitia medicamentului in dictionar
		Daca nu exista medicamentul, se returneaza -1
	*/
	auto getPozitie(const Medicament& m) const;

	/* 
		Returneaza pozitia medicamentului in reteta
		Daca nu exista medicamentul, se returneaza -1
	*/
	int getPozitieReteta(const Medicament& m) const;
public:
	Repo() = default;
	Repo(const Repo& ot) = delete;

	/*
		Adauga un medicament in dictionar
		Arunca exceptie daca medicamentul deja exista
	*/
	void add(const Medicament& m);

	bool exist(const Medicament& m) const;

	/*
		Cauta un medicament si il returneaza
		Arunca exceptie daca medicamentul nu exista
	*/
	Medicament findMed(string denumire) const;

	/*
		Modifica un medicament
		Arunca exceptie daca medicamentul nu exista
	*/
	void modify(const Medicament& m, int camp);

	/*
		Sterge un medicament
		Arunca exceptie daca medicamentul nu exista
	*/
	void del(const Medicament& m);

	/* Returneaza lista de medicamente */
	vector<Medicament> getMeds();

	/*
		Adauga un medicament in vector
		Medicamentul poate fi adaugat de mai multe ori
	*/
	void addReteta(const Medicament& m);

	/* Goleste reteta */
	void clearAll();

	/* Returneaza medicamentele din reteta */
	vector<pair<Medicament, int>> afiseazaReteta();

	int sizeReteta() const;
};