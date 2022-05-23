#include "Medicament.h"

string Medicament::getDenumire() const
{
	return denumire;
}

string Medicament::getProducator() const
{
	return producator;
}

double Medicament::getPret() const
{
	return pret;
}

int Medicament::getSubstantaActiva() const
{
	return substantaActiva;
}

void Medicament::setPret(double value)
{
	pret = value;
}

void Medicament::setSubstantaActiva(int value)
{
	substantaActiva = value;
}