#pragma once

typedef int TElem;

#define NULL_TELEMENT 0
#define c1 0.5
#define c2 0.5

class Matrice
{
private:
	/* aici e reprezentarea */
	struct Triplet
	{
		int linie;
		int coloana;
		TElem valoare;
	};

	Triplet* T;
	int m;
	int totalLinii, totalColoane;

	// functia de dispersie
	// verificare patratica
	long long d(TElem e, int i) const;

	// functia care da hashcode-ul format din linie si coloana
	TElem hashCode(int linie, int coloana) const;

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);

	// determina suma elementelor de pe o coloana j
	TElem suma(int j);

	//destructor
	~Matrice() {};

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;

	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;

	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem);
};