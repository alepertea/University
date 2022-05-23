#pragma once
#include "Medicament.h"
#include "Repository.h"
#include "Validator.h"
#include "Lista.h"
#include <vector>
#include <string>
#include <functional>

using std::vector;
using std::function;

class Service
{
private:
	Repo& repo;
	Validator& val;

public:
	Service(Repo& repo, Validator& val) : repo{ repo }, val{ val } {}

	Service(const Service& ot) = delete;
	Service() = default;

	/* Returneaza lista de medicamente */
	Lista<Medicament> getMeds() const;

	/*
		Valideaza campurile introduse si adauga medicamentul daca e valid.
		Daca medicamentul e invalid, se afiseaza mesaje de eroare.
	*/
	void addMed(const string& denumire, const string& producator, const double& pret, const int& substantaActiva);

	/* Valideaza campurile introduse si modifica medicamentul, daca exista */
	void modifyMed(const string& denumire, const string& producator, const double& pret, const int& substantaActiva, const int& camp);

	/* Cauta medicament dupa denumirea si producatorul introdus de utilizator */
	const Medicament& findMed(const string& denumire, const string& producator);

	/* Sterge medicament dupa denumirea si producatorul introdus de utilizator */
	void deleteMed(const string& denumire, const string& producator);

	/* Afiseaza medicamente dupa un anumit criteriu */
	Lista<Medicament> filterMeds(const double& pret, const int& substantaActiva, const int& criteriu) const;

	/* Sorteaza medicamentele dupa denumire */
	Lista<Medicament> sortByDenumire();

	/* Sorteaza medicamentele dupa producator */
	Lista<Medicament> sortByProducator();

	/* Sorteaza medicamentele dupa substanta activa + pret */
	Lista<Medicament> sortBySubstantaSiPret();
};