#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c) : col(c) 
{
	curent = 0;
	frecventa = 1;
}

void IteratorColectie::prim() 
{
	/*
		Complexitate:
			- timp: teta(1)
			- spatiu: teta(1)
	*/
	curent = 0;
	frecventa = 1;
}

void IteratorColectie::urmator() 
{
	/*
		Complexitate:
			- timp: teta(1)
			- spatiu: teta(1)
	*/
	if (frecventa < col.v[curent].frecv)
		frecventa++;
	else
	{
		curent++;
		frecventa = 1;
	}
}


bool IteratorColectie::valid() const 
{
	/*
		Complexitate:
			- timp: teta(1)
			- spatiu: teta(1)
	*/
	return curent < col.len;
}



TElem IteratorColectie::element() const 
{
	/*
		Complexitate:
			- timp: teta(1)
			- spatiu: teta(1)
	*/
	if (valid())
		return col.v[curent].el;
	return -1;
}