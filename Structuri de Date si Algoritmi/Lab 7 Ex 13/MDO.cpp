#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

int MDO::minim(int nod)
{
	// O(h), h - inaltimea
	if (nod == NULL_POINTER)
		return NULL_POINTER;
	else
		while (this->nod[nod].stanga != NULL_POINTER)
			nod = this->nod[nod].stanga;
	return nod;
}

void MDO::redimensionare()
{
	// Teta(n^2), n - capacitate / 2

	this->capacitate *= 2;
	Nod* nodNou = new Nod[this->capacitate];
	for (int i = 0; i < this->capacitate / 2; i++)
	{
		nodNou[i].cheie = this->nod[i].cheie;
		nodNou[i].valori = this->nod[i].valori;
		nodNou[i].capacitateVector = this->nod[i].capacitateVector;
		nodNou[i].stanga = nod[i].stanga;
		nodNou[i].dreapta = nod[i].dreapta;
	}

	for (int i = this->capacitate / 2; i < this->capacitate; i++)
	{
		nodNou[i].cheie = NULL_TCHEIE;
		nodNou[i].capacitateVector = 10;
		nodNou[i].valori = new TValoare[10];
		for (int j = 0; j < 10; j++)
			nodNou[i].valori[j] = NULL_TVALOARE;
		nodNou[i].stanga = NULL_POINTER;
		nodNou[i].dreapta = NULL_POINTER;
	}

	delete[] this->nod;
	this->nod = nodNou;
}

MDO::MDO(Relatie r)
{
	// Teta(n^2), n - capacitatea

	this->rel = r;
	this->capacitate = 10;
	this->dimensiune = 0;
	this->radacina = NULL_POINTER;
	this->primLiber = 0;

	this->nod = new Nod[this->capacitate];
	for (int i = 0; i < this->capacitate; i++)
	{
		this->nod[i].cheie = NULL_TCHEIE;
		this->nod[i].stanga = NULL_POINTER;
		this->nod[i].dreapta = NULL_POINTER;
		this->nod[i].capacitateVector = 10;
		this->nod[i].valori = new TValoare[10];

		for (int j = 0; j < this->nod->capacitateVector; j++)
			this->nod[i].valori[j] = NULL_TVALOARE;
	}
}

int MDO::adauga_rec(int rad, TCheie c, TValoare v)
{
	// Best Case: Teta(1)
	// Worst Case: Teta(h + capacitateVector)
	// O(h + capacitateVector) ~ O(h) amortizat, h - inaltimea

	if (rad == NULL_POINTER)
	{
		this->nod[this->primLiber].cheie = c;
		this->nod[this->primLiber].capacitateVector = 10;
		this->nod[this->primLiber].stanga = NULL_POINTER;
		this->nod[this->primLiber].dreapta = NULL_POINTER;
		this->nod[this->primLiber].valori = new TValoare[10];
		for (int i = 0; i < 10; i++)
			this->nod[this->primLiber].valori[i] = NULL_TVALOARE;
		this->nod[this->primLiber].valori[0] = v;
		rad = this->primLiber;
		this->primLiber++;
	}
	else if (this->nod[rad].cheie == c)
	{
		int i;
		for (i = 0; i < this->nod[rad].capacitateVector; i++)
			if (this->nod[rad].valori[i] == NULL_TVALOARE)
				break;
		if (i == this->nod[rad].capacitateVector)
		{
			this->nod[rad].capacitateVector *= 2;
			TValoare* valoriNou = new TValoare[this->nod[rad].capacitateVector];

			for (int i = 0; i < this->nod[rad].capacitateVector / 2; i++)
				valoriNou[i] = this->nod[rad].valori[i];
			for (int i = this->nod[rad].capacitateVector / 2; i < this->nod[rad].capacitateVector; i++)
				valoriNou[i] = NULL_TVALOARE;

			delete this->nod[rad].valori;
			this->nod[rad].valori = valoriNou;
		}
		this->nod[rad].valori[i] = v;
	}
	else if (this->rel(c, this->nod[rad].cheie) == true)
		this->nod[rad].stanga = this->adauga_rec(this->nod[rad].stanga, c, v);
	else
		this->nod[rad].dreapta = this->adauga_rec(this->nod[rad].dreapta, c, v);
	return rad;
}

void MDO::adauga(TCheie c, TValoare v)
{
	// O(h) amortizat, h - inaltimea
	if (this->dimensiune == this->capacitate - 1)
		redimensionare();
	this->radacina = this->adauga_rec(this->radacina, c, v);
	this->dimensiune++;
}

TCheie MDO::cheieMaxima() const
{
	// O(h), h - inaltimea

	if (this->radacina == NULL_POINTER)
		return NULL_TCHEIE;

	int nodCurent = this->radacina;
	if(this->rel(2,3) == true)
	{
		while (this->nod[nodCurent].dreapta != NULL_POINTER)
			nodCurent = this->nod[nodCurent].dreapta;
		return this->nod[nodCurent].cheie;
	}
	else
	{
		while (this->nod[nodCurent].stanga != NULL_POINTER)
			nodCurent = this->nod[nodCurent].stanga;
		return this->nod[nodCurent].cheie;
	}
}

vector<TValoare> MDO::cauta(TCheie c) const 
{
	// O(h + capacitate) ~ O(h), h - inaltimea

	vector<TValoare> values;
	int curent = this->radacina;
	while (curent != NULL_POINTER)
	{
		if (this->nod[curent].cheie == c)
		{
			for (int i = 0; i < this->nod[curent].capacitateVector; i++)
			{
				if (this->nod[curent].valori[i] == NULL_TVALOARE)
					break;
				values.push_back(this->nod[curent].valori[i]);
			}
			return values;
		}

		if (this->rel(c, this->nod[curent].cheie) == true)
			curent = this->nod[curent].stanga;
		else
			curent = this->nod[curent].dreapta;
	}

	return values;
}

int MDO::sterge_rec(int rad, TCheie c, TValoare v, bool& gasit)
{
	// Best Case: Teta(capacitateVector), cheia e radacina si valoarea e pe prima pozitie
	// Worst Case: Teta(h + capacitateVector)
	// O(h + capacitateVector) ~ O(h), h - inaltimea

	if (rad == NULL_POINTER)
		return NULL_POINTER;
	else if (this->rel(c, this->nod[rad].cheie) == true && c != this->nod[rad].cheie)
	{
		this->nod[rad].stanga = this->sterge_rec(this->nod[rad].stanga, c, v, gasit);
		return rad;
	}
	else if (this->rel(c, this->nod[rad].cheie) == false)
	{
		this->nod[rad].dreapta = this->sterge_rec(this->nod[rad].dreapta, c, v, gasit);
		return rad;
	}
	else
	{
		for (int i = 0; i < this->nod[rad].capacitateVector && gasit == false; i++)
			if (this->nod[rad].valori[i] == v)
			{
				for (int j = i; j < this->nod[rad].capacitateVector - 1; j++)
					this->nod[rad].valori[i] = this->nod[rad].valori[i + 1];
				this->nod[rad].valori[this->nod[rad].capacitateVector - 1] = NULL_TVALOARE;
				gasit = true;
			}
		if (this->nod[rad].valori[0] != NULL_TVALOARE)
			return rad;
		else
			if (this->nod[rad].stanga != NULL_POINTER && this->nod[rad].dreapta != NULL_POINTER)
			{
				int temp = this->minim(this->nod[rad].dreapta);
				this->nod[rad].cheie = this->nod[temp].cheie;
				delete this->nod[rad].valori;
				this->nod[rad].valori = this->nod[temp].valori;
				this->nod[rad].capacitateVector = this->nod[temp].capacitateVector;
				for (int i = 0; i < this->nod[rad].capacitateVector && this->nod[rad].cheie != NULL_TCHEIE; i++)
					this->nod[rad].dreapta = this->sterge_rec(this->nod[rad].dreapta, c, nod[rad].valori[i], gasit);
			}
			else
			{
				int temp = rad;
				int radNoua;
				if (this->nod[rad].stanga == NULL_POINTER)
					radNoua = this->nod[rad].dreapta;
				else
					radNoua = this->nod[rad].stanga;
				return radNoua;
			}
	}
}

bool MDO::sterge(TCheie c, TValoare v)
{
	// O(h + capacitateVector) ~ O(h), h - inaltimea
	bool gasit = false;
	this->radacina = this->sterge_rec(this->radacina, c, v, gasit);
	if(gasit == true)
		this->dimensiune--;
	return gasit;
}

int MDO::dim() const
{
	// Teta(1)
	return this->dimensiune;
}

bool MDO::vid() const 
{
	// Teta(1);
	return this->dimensiune == 0;
}

IteratorMDO MDO::iterator() const
{
	return IteratorMDO(*this);
}

MDO::~MDO() 
{
	// Teta(n), n - capacitatea
	for (int i = 0; i < this->capacitate; i++)
		delete[] this->nod[i].valori;
	delete[] this->nod;
}