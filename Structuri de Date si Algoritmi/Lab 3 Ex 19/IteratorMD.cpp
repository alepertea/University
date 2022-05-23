#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md) : md(_md) 
{
	// teta(1)
	this->curent = md.prim;
	if (this->curent != nullptr)
		this->itL = this->curent->info.second;
}

TElem IteratorMD::element() const
{
	// teta(1)
	if (valid() == false)
		throw exception();
	TCheie c = this->curent->info.first;
	TValoare v = this->itL->val;
	return pair <TCheie, TValoare>(c, v);
}

bool IteratorMD::valid() const 
{
	// teta(1)
	if (this->curent == nullptr || this->itL == nullptr)
		return false;
	return true;
}

void IteratorMD::urmator()
{
	// teta(1)
	this->itL = this->itL->urm;
	if (valid() == false)
	{
		this->curent = this->curent->urm;
		if (this->curent != nullptr)
			this->itL = this->curent->info.second;
	}
}

void IteratorMD::prim() 
{
	// teta(1)
	this->curent = md.prim;
	if (curent != nullptr)
		this->itL = curent->info.second;
}
