#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d) 
{
	// O(h)
	int nod = dict.radacina;
	while (nod != NULL_POINTER)
	{
		this->s.push(nod);
		nod = dict.nod[nod].stanga;
	}
	if (!this->s.empty())
		this->nodCurent = s.top();
	else
		this->nodCurent = NULL_TVALOARE;
	this->indexValoare = 0;
}

void IteratorMDO::prim()
{
	// O(h)
	while (!this->s.empty())
		this->s.pop();
	int nod = dict.radacina;
	while (nod != NULL_POINTER)
	{
		this->s.push(nod);
		nod = dict.nod[nod].stanga;
	}
	if (!this->s.empty())
		this->nodCurent = s.top();
	else
		this->nodCurent = NULL_TVALOARE;
	this->indexValoare = 0;
}

void IteratorMDO::urmator()
{
	// O(h)
	if (this->indexValoare < dict.nod[this->nodCurent].capacitateVector - 1)
		this->indexValoare++;
	else
	{
		int nod = this->s.top();
		this->s.pop();
		if (dict.nod[nod].dreapta != NULL_POINTER)
		{
			nod = dict.nod[nod].dreapta;
			while (nod != NULL_POINTER)
			{
				this->s.push(nod);
				nod = dict.nod[nod].stanga;
			}
		}
		if (!this->s.empty())
			this->nodCurent = this->s.top();
		else
			this->nodCurent = NULL_POINTER;
	}
}

bool IteratorMDO::valid() const
{
	// Teta(1)
	return !this->dict.vid() && this->nodCurent != NULL_POINTER;
}

TElem IteratorMDO::element() const
{
	// Teta(1)
	if (this->valid())
		return std::make_pair(dict.nod[this->nodCurent].cheie, dict.nod[this->nodCurent].valori[this->indexValoare]);
}