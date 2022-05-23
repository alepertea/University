#include "Produs.h"

int Produs::getID() const
{
	return this->id;
}

string Produs::getNume() const
{
	return this->nume;
}

string Produs::getTip() const
{
	return this->tip;
}

double Produs::getPret() const
{
	return this->pret;
}

int Produs::getNumarVocale() const
{
	int count = 0;
	string nume = this->getNume();
	for (unsigned int i = 0; i < nume.size(); i++)
		if (nume[i] == 'a' || nume[i] == 'e' || nume[i] == 'i' || nume[i] == 'o' || nume[i] == 'u' || nume[i] == 'A' || nume[i] == 'E' || nume[i] == 'I' || nume[i] == 'O' || nume[i] == 'U')
			count++;
	return count;
}