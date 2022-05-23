#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

Multime::Multime() 
{
	// Teta(cp), cp - capacitatea

	this->cp = 10;
	this->urm = new int[cp];
	this->prec = new int[cp];
	this->e = new TElem[this->cp];

	for (int i = 0; i < this->cp - 1; i++)
		this->urm[i] = i + 1;
	this->urm[cp - 1] = NULL_TELEM;

	this->prim = NULL_TELEM;
	this->primLiber = 0;
}

int Multime::aloca()
{
	// Teta(1)
	int i = this->primLiber;
	this->primLiber = this->urm[this->primLiber];
	return i;
}

void Multime::dealoca(int i)
{
	// Teta(1)
	this->urm[i] = this->primLiber;
	this->primLiber = i;
}

int Multime::creeazaNod(TElem elem)
{
	// Teta(1) amortizat

	if (this->primLiber == NULL_TELEM)
	{
		// redimensionare
		this->cp *= 2;
		int* urmNou = new int[this->cp];
		int* precNou = new int[this->cp];
		int* eNou = new int[this->cp];

		for (int i = 0; i < this->cp / 2; i++)
		{
			urmNou[i] = this->urm[i];
			precNou[i] = this->prec[i];
			eNou[i] = this->e[i];
		}
		delete this->urm;
		delete this->prec;
		delete this->e;

		this->urm = urmNou;
		this->prec = precNou;
		this->e = eNou;

		// reinitializare spatiu liber
		for (int i = this->cp / 2; i < this->cp - 1; i++)
			this->urm[i] = i + 1;
		this->urm[cp - 1] = NULL_TELEM;
		this->primLiber = this->cp / 2;
	}

	int i = aloca();
	this->e[i] = elem;
	this->urm[i] = NULL_TELEM;
	this->prec[i] = NULL_TELEM;
	return i;
}

bool Multime::adauga(TElem elem) 
{
	// O(n), n - nr de elemente din multime

	if (cauta(elem) == true)
		return false;

	int nod = creeazaNod(elem);
	if (this->prim == NULL_TELEM)
		this->prim = nod;
	else
	{
		this->urm[nod] = this->prim;
		this->prec[prim] = nod;
		this->prim = nod;
	}

	return true;
}

bool Multime::sterge(TElem elem) 
{
	// O(n), n - nr de elemente din multime

	int nod = this->prim;
	while (nod != NULL_TELEM && this->e[nod] != elem)
	{
		nod = this->urm[nod];
	}
	if (nod == NULL_TELEM)
		return false;
	
	if (nod == this->prim)
	{
		if(urm[nod] != NULL_TELEM)
			this->prec[urm[nod]] = NULL_TELEM;
		this->prim = this->urm[nod];
		dealoca(nod);
		return true;
	}

	if (this->urm[nod] == NULL_TELEM)
	{
		this->urm[prec[nod]] = NULL_TELEM;
		dealoca(nod);
		return true;
	}

	this->urm[prec[nod]] = this->urm[nod];
	this->prec[urm[nod]] = this->prec[nod];
	dealoca(nod);

	return true;
}

bool Multime::cauta(TElem elem) const
{
	// O(n), n - numarul de elemente din multime

	int curent = this->prim;
	while (curent != NULL_TELEM && this->e[curent] != elem)
	{
		curent = this->urm[curent];
	}
	if (curent == NULL_TELEM)
		return false;
	return true;
}

int Multime::dim() const
{
	// Teta(n), n - numarul de elemente din multime

	int count = 0;
	int curent = this->prim;
	while (curent != NULL_TELEM)
	{
		curent = this->urm[curent];
		count++;
	}
	return count;
}

bool Multime::vida() const 
{
	// Teta(1)
	return this->prim == NULL_TELEM;
}

void Multime::intersectie(const Multime& b)
{
	// Best case: multimile sunt identice => teta(n*m)
	// Worst case: intersectia e multimea vida => teta(n*m)
	// Overall: teta(m*n)

	int curent = b.prim;
	while (curent != NULL_TELEM)
	{
		bool gasit = cauta(b.e[curent]);
		if (gasit == false)
		{
			sterge(e[curent]);
		}
		curent = urm[curent];
	}
}

Multime::~Multime() 
{
	// Teta(1)
	delete urm;
	delete prec;
	delete e;
}

IteratorMultime Multime::iterator() const
{
	// Teta(1)
	return IteratorMultime(*this);
}
