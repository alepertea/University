#pragma once
#include "Medicament.h"
#include "Export.h"
#include <vector>
#include <string>
#include <ostream>
#include <map>
#include <algorithm>
#include <random>
#include <numeric>
#include <stdlib.h>
#include "Observer.h"

using namespace std;

class VirtualRepo
{
protected:
	double error = 0;
public:
	virtual void add(const Medicament& m) = 0;

	virtual bool exist(const Medicament& m) const = 0;

	virtual Medicament findMed(string denumire) const = 0;

	virtual void modify(const Medicament& m, int camp) = 0;

	virtual void del(const Medicament& m) = 0;

	virtual vector<Medicament> getMeds() = 0;

	virtual double getErrorPercentage() const = 0;
};

class RepositoryException
{
private:
	string eroare;
public:
	RepositoryException(string e) : eroare{ e } {}

	friend ostream& operator<<(ostream& out, const RepositoryException& ex);
};

ostream& operator<<(ostream& out, const RepositoryException& ex);

class Repo : public VirtualRepo, public Observable
{
private:
	/* Dictionar de medicamente */
	map<string, Medicament> meds;

	/*
		Returneaza pozitia medicamentului in dictionar
		Daca nu exista medicamentul, se returneaza -1
	*/
	auto getPozitie(const Medicament& m) const;

public:
	Repo() = default;
	Repo(double error);

	/*
		Adauga un medicament in dictionar
		Arunca exceptie daca medicamentul deja exista
	*/
	virtual void add(const Medicament& m) override;

	bool exist(const Medicament& m) const override;

	/*
		Cauta un medicament si il returneaza
		Arunca exceptie daca medicamentul nu exista
	*/
	Medicament findMed(string denumire) const override;

	/*
		Modifica un medicament
		Arunca exceptie daca medicamentul nu exista
	*/
	virtual void modify(const Medicament& m, int camp) override;

	/*
		Sterge un medicament
		Arunca exceptie daca medicamentul nu exista
	*/
	virtual void del(const Medicament& m) override;

	/* Returneaza lista de medicamente */
	vector<Medicament> getMeds() override;

	double getErrorPercentage() const override;
};

class Reteta : public Observable
{
private:
	/* Vector de medicamente pentru reteta */
	vector<Medicament> reteta;

	/*
		Returneaza pozitia medicamentului in reteta
		Daca nu exista medicamentul, se returneaza -1
	*/
	int getPozitieReteta(const Medicament& m) const;

public:
	Reteta() = default;
	Reteta(const Reteta& ot) = default;
	~Reteta() = default;

	/*
		Adauga un medicament in vector
		Medicamentul poate fi adaugat de mai multe ori
	*/
	void addReteta(const Medicament& m);

	/*
		Sterge un medicament din reteta
		Arunca exceptie daca medicamentul e inexistent
	*/
	virtual void stergeInReteta(const Medicament& m);

	/* Goleste reteta */
	void clearAll();

	/* Cauta un medicament in reteta */
	Medicament findMed(const string& denumire);

	/* Returneaza medicamentele din reteta */
	vector<Medicament> getReteta();

	/* Returneaza numarul de medicamente din reteta */
	size_t sizeReteta() const;
};