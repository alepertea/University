#pragma once
#include "Medicament.h"
#include "FileRepo.h"
#include "Validator.h"
#include "Export.h"
#include "Undo.h"
#include "DTO.h"
#include <vector>
#include <string>
#include <random>
#include <numeric>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;

class Service : public Observable
{
private:
	VirtualRepo& repo;
	Validator& val;
	Reteta& ret;
	vector<unique_ptr<ActiuneUndo>> undoActions;

	/* Genereaza un string aleator */
	string randomString();

public:
	Service(VirtualRepo& repo, Validator& val, Reteta& ret) : repo{ repo }, val{ val }, ret{ ret } {}

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

	/* Determina suma preturilor */
	double stats() const;

	/* Returneaza un vector de DTO in functie de substanta activa */
	vector<DTO> makeDTOVector() const;

	void undo();

	/*
		Adauga un medicament in vector
		Medicamentul poate fi adaugat de mai multe ori
	*/
	void addReteta(const string& denumire, const string& producator, const double& pret, const int& substantaActiva);

	/* Goleste reteta */
	void clearAll();

	/* Cauta un medicament in reteta */
	Medicament findMedReteta(const string& denumire);

	/* Returneaza medicamentele din reteta */
	vector<Medicament> getReteta();

	/* Returneaza numarul de medicamente din reteta */
	size_t sizeReteta() const;

	/* Genereaza medicamente aleator */
	void random(int nrMeds);

	void exportCSV(const string& filename) const;

	void exportHTML(const string& filename) const;
};