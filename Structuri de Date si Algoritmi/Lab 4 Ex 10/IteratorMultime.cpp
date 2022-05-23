#include "IteratorMultime.h"
#include "Multime.h"

IteratorMultime::IteratorMultime(const Multime& m) : multime(m)
{
	// Teta(1)
	this->curent = m.prim;
}

void IteratorMultime::prim() 
{
	// Teta(1)
	this->curent = multime.prim;
}

void IteratorMultime::urmator() 
{
	// Teta(1)
	this->curent = multime.urm[this->curent];
}

TElem IteratorMultime::element() const
{
	// Teta(1)
	return multime.e[this->curent];
}

bool IteratorMultime::valid() const
{
	// Teta(1)
	return this->curent != NULL_TELEM;
}