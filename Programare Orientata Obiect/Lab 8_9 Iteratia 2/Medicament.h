#pragma once
#include <string>
using std::string;

class Medicament
{
private:
	string denumire;
	string producator;
	double pret;
	int substantaActiva;

public:
	/* Getter pentru denumire */
	string getDenumire() const;

	/* Getter pentru producator */
	string getProducator() const;

	/* Getter pentru pret */
	double getPret() const;

	/* Getter pentru cantitatea de substanta activa */
	int getSubstantaActiva() const;

	/* Setter pentru pret */
	void setPret(double value);

	/* Setter pentru cantitatea de substanta activa */
	void setSubstantaActiva(int value);

	/* Constructor */
	Medicament(const string denumire, const string producator, const double pret, const int substantaActiva) :denumire{ denumire }, producator{ producator }, pret{ pret }, substantaActiva{ substantaActiva } {}

};

/* Compara denumirile a doua medicamente si returneaza true daca sunt in ordine alfabetica */
bool cmpDenumire(const Medicament& m1, const Medicament& m2);

/* Compara producatorii a doua medicamente si returneaza true daca sunt in ordine alfabetica */
bool cmpProducator(const Medicament& m1, const Medicament& m2);

/* Compara substanta activa si pretul a doua medicamente */
bool cmpSubstantaSiPret(const Medicament& m1, const Medicament& m2);