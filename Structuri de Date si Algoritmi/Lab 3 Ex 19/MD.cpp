#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>

using namespace std;


MD::MD()
{
	// teta(1)
	this->prim = nullptr;
}


bool MD::listaVida(TCheie c) const
{
	// best case: teta(1)
	// worst case: teta(n)
	// overall: O(n)

	TNod* curent = this->prim;
	while (curent != nullptr && curent->info.first != c)
		curent = curent->urm;
	if (curent == nullptr)
		return true;
	if (curent->info.second == nullptr)
		return true;
	return false;
}


void MD::adauga(TCheie c, TValoare v)
{
	// best case: teta(n)
	// worst case: O(n)
	// overall: O(n), n - numarul de chei

	vector<TValoare> listaValori = this->cauta(c);

	if (listaValori.size() == 0) // cheia nu exista
	{	//teta(1), pentru cautare e teta(n)
 		TNod* nou = new TNod;
		nou->info.first = c;

		TLista* valoare = new TLista;
		valoare->val = v;
		valoare->urm = nullptr;
		
		nou->info.second = valoare;
		nou->urm = this->prim;

		prim = nou;
	}
	else
	{	// O(n), teta(n) pentru cautare
		TNod* curent = this->prim;
		while (curent->info.first != c)
			curent = curent->urm;
		TLista* valoare = new TLista;
		valoare->val = v;
		valoare->urm = curent->info.second;
		curent->info.second = valoare;
	}
}


bool MD::sterge(TCheie c, TValoare v) 
{
	// O(n)

	vector<TValoare> listaValori = this->cauta(c); // teta(n)
	if(listaValori.size() == 0)
		return false;

	TNod* curent = this->prim;
	while (curent != nullptr && curent->info.first != c)	// O(n)
		curent = curent->urm;

	if (curent == nullptr)	// cheia nu exista
		return false;

	TLista* nod = curent->info.second;
	if (nod->val == v)				// stergem primul nod
	{
		curent->info.second = nod->urm;
		nod->urm = nullptr;
		delete[] nod;
	}
	else
	{	// O(m)
		while (nod->urm != nullptr && nod->urm->val != v)	// vreau sa ajung la nodul precedent nodului pe care il sterg
			nod = nod->urm;
		if (nod->urm == nullptr && nod->val != v)	// valoarea nu exista
			return false;
		TLista* aux = nod->urm;
		nod->urm = nod->urm->urm;
		delete[] aux;
	}
	
	if (listaVida(c))				// cheia nu mai are nicio valoare asociata, deci o stergem si pe ea
	{
		TNod* nod = this->prim;
		if (nod->info.first == c)	// daca cheia e prima
		{
			this->prim = this->prim->urm;
			delete[] nod;
		}
		else
		{
			while (nod->urm->urm != nullptr && nod->urm->info.first != c)
				nod = nod->urm;
			TNod* aux = nod->urm;
			nod->urm = nod->urm->urm;
			delete[] aux;
		}
	}
	
	return true;
}


vector<TValoare> MD::cauta(TCheie c) const
{
	// best case: teta(m), m - numar de elemente din lista de valori
	// worst case: teta(n + m) ~ teta(n), n - numar de chei distincte
	// Overall: teta(n)

	vector<TValoare> rez;
	TNod* curent = this->prim;

	while (curent != nullptr && curent->info.first != c)
		curent = curent->urm;

	if (curent == nullptr)
		return rez;

	TLista* nod = curent->info.second;
	while (nod != nullptr)
	{
		rez.push_back(nod->val);
		nod = nod->urm;
	}

	return rez;
}


int MD::dim() const 
{
	// teta(md), md - suma lungimilor listelor de valori

	TNod* curent = this->prim;
	int count = 0;
	while (curent != nullptr)
	{
		TLista* nod = curent->info.second;
		while (nod != nullptr)
		{
			count++;
			nod = nod->urm;
		}
		curent = curent->urm;
	}
	return count;
}


bool MD::vid() const
{
	// teta(1)
	return prim == nullptr;
}

IteratorMD MD::iterator() const
{
	return IteratorMD(*this);
}


TCheie MD::cheieMaxima() const
{
	// teta(n), n - numarul de chei distincte

	if (this->prim == nullptr)
		return NULL_TCHEIE;

	TCheie max = 0;

	TNod* curent = this->prim;
	while (curent != nullptr)
	{
		if (curent->info.first > max)
			max = curent->info.first;
		curent = curent->urm;
	}

	return max;
}


MD::~MD() 
{
	// teta(md), md - suma lungimilor listelor de valori
	while (this->prim != nullptr)
	{
		TNod* p = this->prim;
		TLista* nod = p->info.second;
		while (nod != nullptr)
		{
			TLista* copie = nod;
			nod = nod->urm;
			delete[] copie;
		}
		this->prim = this->prim->urm;
		delete[] p;
	}
}
