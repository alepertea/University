#pragma once
#include "Validator.h"
#include "Observer.h"
#include "Produs.h"
#include "Repository.h"

class Service : public Observable
{
private:
	Repo& r;
	Valid& v;

public:
	Service(Repo& r, Valid& v) :r{ r }, v{ v }{}

	// valideaza datele si incearca sa adauge daca ele sunt valide
	// returneaza 0 daca adaugarea s-a efectuat cu succes
	// altfel, returneaza unul dintre codurile de eroare de la valid sau de la repo
	int addProduct(const int& id, const string& nume, const string& tip, const double& pret);

	// returneaza toate produsele din repo
	vector<Produs> getProducts();

	// returneaza produsele din repo sortate dupa pret
	vector<Produs> sortByPrice();

	// filtreaza produsele dupa pret
	vector<Produs> filterProducts(const double& pret);

	int getNumberOfProducts(const string& tip);
};