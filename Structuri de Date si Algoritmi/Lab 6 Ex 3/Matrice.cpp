#include "Matrice.h"
#include <exception>
#include <iostream>
#include <string>

using namespace std;

Matrice::Matrice(int m, int n)
{
	// Teta(m), m - numarul de pozitii din tabela

	if (m <= 0 || n <= 0)
	{
		throw exception();
	}

	this->m = 16;
	this->T = new Triplet[this->m];
	this->totalLinii = m;
	this->totalColoane = n;

	Triplet tNull;
	tNull.linie = NULL_TELEMENT;
	tNull.coloana = NULL_TELEMENT;
	tNull.valoare = NULL_TELEMENT;
	for (int i = 0; i < this->m; i++)
	{
		this->T[i] = tNull;
	}
}

TElem Matrice::hashCode(int linie, int coloana) const
{
	// Teta(1)
	return stoi(to_string(linie) + to_string(coloana));
}

long long Matrice::d(TElem e, int i) const
{
	// Teta(1)

	long long p = c1 * i;
	long long k = c2 * i * i;
	return (long long)(((long long)(e % this->m) + p + k) % this->m);
}

int Matrice::nrLinii() const
{
	// Teta(1)
	return this->totalLinii;
}

int Matrice::nrColoane() const 
{
	// Teta(1)
	return this->totalColoane;
}

TElem Matrice::suma(int j)
{
	// Teta(m), m - numarul de pozitii din tabela

	int suma = 0;
	for (int i = 0; i < this->m; i++)
	{
		if (T[i].coloana == j)
		{
			suma += T[i].valoare;
		}
	}
	return suma;
}

TElem Matrice::element(int i, int j) const
{
	// O(m), m - numarul de pozitii in tabela

	if (i < 0 || j < 0 || i >= this->totalLinii || j >= this->totalColoane)
		throw exception();

	int k = 0;
	do
	{
		long long disp = d(hashCode(i, j), k);
		if (T[disp].linie == i && T[disp].coloana == j)
			return T[disp].valoare;
		else
			k++;
	} while (k < this->m);

	return NULL_TELEMENT;
}

TElem Matrice::modifica(int i, int j, TElem e)
{
	// O(m^2), O(m) amortizat, m - numarul de pozitii din tabela

	if (i < 0 || j < 0 || i >= this->totalLinii || j >= this->totalColoane)
		throw exception();

	int k = 0;

	do
	{
		long long disp = d(hashCode(i, j), k);
		if (T[disp].valoare == NULL_TELEMENT)
		{
			T[disp].linie = i;
			T[disp].coloana = j;
			T[disp].valoare = e;
			return e;
		}
		if (T[disp].linie == i && T[disp].coloana == j)
		{
			int elem = T[disp].valoare;
			T[disp].valoare = e;
			return elem;
		}
		k++;
	} while (k < this->m);

	if (k == this->m)
	{
		this->m = this->m * 2;
		Triplet* Tnou = new Triplet[this->m];
		Triplet tNull;
		tNull.linie = NULL_TELEMENT;
		tNull.coloana = NULL_TELEMENT;
		tNull.valoare = NULL_TELEMENT;

		for (int i = 0; i < this->m; i++)
		{
			Tnou[i] = tNull;
		}

		for (int j = 0; j < this->m / 2; j++)
		{
			if (this->T[j].valoare != NULL_TELEMENT)
			{
				for (int p = 0; p < this->m; p++)
				{
					long long disp = this->d(hashCode(T[j].linie, T[j].coloana), p);
					if (Tnou[disp].valoare == NULL_TELEMENT)
					{
						Tnou[disp].linie = T[j].linie;
						Tnou[disp].coloana = T[j].coloana;
						Tnou[disp].valoare = T[j].valoare;
						break;
					}
				}
			}
		}
		delete[] this->T;
		this->T = Tnou;

		int k = this->m / 2;
		do
		{
			long long disp = d(hashCode(i, j), k);
			if (T[disp].valoare == NULL_TELEMENT)
			{
				T[disp].linie = i;
				T[disp].coloana = j;
				T[disp].valoare = e;
				return e;
			}
			else
			{
				k++;
			}
		} while (k < this->m);
	}
}