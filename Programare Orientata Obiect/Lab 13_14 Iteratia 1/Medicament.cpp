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

bool cmpDenumire(const Medicament& m1, const Medicament& m2)
{
	return m1.getDenumire() < m2.getDenumire();
}

bool cmpProducator(const Medicament& m1, const Medicament& m2)
{
	return m1.getProducator() < m2.getProducator();
}

bool cmpSubstantaSiPret(const Medicament& m1, const Medicament& m2)
{
	if (m1.getSubstantaActiva() == m2.getSubstantaActiva())
		return m1.getPret() < m2.getPret();
	return m1.getSubstantaActiva() < m2.getSubstantaActiva();
}