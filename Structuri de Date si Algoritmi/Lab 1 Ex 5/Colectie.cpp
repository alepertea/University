#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>

using namespace std;

Colectie::Colectie()
{
	cp = 30;
	len = 0;
	v = new Vector[cp];

	for (int i = 0; i < cp; i++)
	{
		v[i].el = 0;
		v[i].frecv = 0;
	}
}

void Colectie::adauga(TElem elem) 
{
	/*
		Complexitate:
			- timp: teta(n)
			- spatiu: teta(1)

	*/
	int ok = 0;
	for (int i = 0; i < len; i++)
		if (elem == v[i].el)
		{
			ok = 1;
			v[i].frecv++;
		}
	if (ok == 0)
	{
		if (len == cp)
		{
			cp = cp * 2;
			Vector* vectorNou = new Vector[cp];
			for (int i = 0; i < cp / 2; i++)
				vectorNou[i] = v[i];
			delete[]v;
			v = vectorNou;
		}
		v[len].el = elem;
		v[len].frecv = 1;
		len++;
	}
}

bool Colectie::sterge(TElem elem) 
{
	/*
		Complexitate: 
			- timp: CF - teta(n)
					CD - teta(n)
					=> CT - O(n^2)
			- spatiu: teta(1)
	*/
	int ok = 1;
	for (int i = 0; i < len; i++)
	{
		if (elem == v[i].el)
		{
			ok = 0;
			if (v[i].frecv == 1)
			{
				for (int j = i; j < len - 1; j++)
					v[j] = v[j + 1];
				len--;
			}
			else
				v[i].frecv--;
		}
	}
	if (ok == 0)
		return true;
	return false;
}

bool Colectie::cauta(TElem elem) const 
{
	/*
		Complexitate:
			- timp: O(n)
			- spatiu: teta(1)
	*/
	for (int i = 0; i < len; i++)
		if (elem == v[i].el)
			return true;
	return false;
}

int Colectie::nrAparitii(TElem elem) const
{
	/*
		Complexitate:
			- timp: O(n)
			- spatiu: teta(1)
	*/
	for (int i = 0; i < len; i++)
		if (elem == v[i].el) 
			return v[i].frecv;
	return 0;
}

int Colectie::dim() const
{
	/*
		Complexitate:
			- timp: teta(n)
			- spatiu: teta(1)
	*/
	int nrElem = 0;
	for (int i = 0; i < len; i++)
		nrElem += v[i].frecv;
	return nrElem;
}

bool Colectie::vida() const
{
	/*
		Complexitate:
			- timp: teta(1)
			- spatiu: teta(1)
	*/
	return len == 0;
}

IteratorColectie Colectie::iterator() const 
{
	return IteratorColectie(*this);
}

Colectie::~Colectie() 
{
	delete[]v;
}

