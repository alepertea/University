#pragma once
#include "Medicament.h"
#include "Repository.h"
#include "Validator.h"
#include <vector>
#include <string>
#include <functional>
#include <random>
#include <numeric>
#include <stdlib.h>

using std::vector;
using std::function;

class Service
{
private:
	Repo& repo;
	Validator& val;

	/* Genereaza un string aleator */
	string randomString();

public:
	Service(Repo& repo, Validator& val) : repo{ repo }, val{ val } {}

	Service(const Service& ot) = delete;
	Service() = default;

	/* Returneaza lista de medicamente */
	vector <Medicament> getMeds() const;

	/*
		Valideaza campurile introduse si adauga medicamentul daca e valid.
		Daca medicamentul e invalid, se afiseaza mesaje de eroare.
	*/
	void addMed(const string& denumire, const string& producator, const double& pret, const int& substantaActiva);

	/* Valideaza campurile introduse si modifica medicamentul, daca exista */
	void modifyMed(const string& denumire, const string& producator, const double& pret, const int& substantaActiva, const int& camp);

	/* Cauta medicament dupa denumirea si producatorul introdus de utilizator */
	Medicament findMed(const string& denumire);

	/* Sterge medicament dupa denumirea si producatorul introdus de utilizator */
	void deleteMed(const string& denumire, const string& producator);

	/* Afiseaza medicamente dupa un anumit criteriu */
	vector<Medicament> filterMeds(const double& pret, const int& substantaActiva, const int& criteriu) const;

	/* Sorteaza medicamentele dupa denumire */
	vector<Medicament> sortByDenumire();

	/* Sorteaza medicamentele dupa producator */
	vector<Medicament> sortByProducator();

	/* Sorteaza medicamentele dupa substanta activa + pret */
	vector<Medicament> sortBySubstantaSiPret();

	/* Creeaza medicamentul, il valideaza si il adauga la reteta */
	void addReteta(const string& denumire, const string& producator, const double& pret, const int& substantaActiva);

	/* Goleste reteta */
	void clearAll();

	/* Genereaza medicamente aleator */
	void random(int nrMeds);

	/* Tipareste toate medicamentele din reteta */
	vector<pair<Medicament, int>> afiseazaReteta();

	int sizeReteta() const;
};