#pragma once
#include "Medicament.h"
#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

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
	/* Vector de medicamente */
	vector <Medicament> meds;

	/*
		Returneaza pozitia medicamentului in sir
		Daca nu exista medicamentul, se returneaza -1
	*/
	int getPozitie(const Medicament& m) const;
public:
	Repo() = default;
	Repo(const Repo& ot) = delete;

	/*
		Adauga un medicament la lista
		Arunca exceptie daca medicamentul deja exista
	*/
	void add(const Medicament& m);

	bool exist(const Medicament& m) const;

	/*
		Cauta un medicament si il returneaza
		Arunca exceptie daca medicamentul nu exista
	*/
	const Medicament& find(string denumire, string producator) const;

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
};