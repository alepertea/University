#include "Joc.h"

int Joc::getID() const
{
    return this->id;
}

int Joc::getDim() const
{
    return this->dim;
}

string Joc::getTabla() const
{
    return this->tabla;
}

char Joc::getJucator() const
{
    return this->jucator;
}

string Joc::getStare() const
{
    return this->stare;
}

void Joc::setID(const int& idNou)
{
    this->id = idNou;
}

void Joc::setDim(const int& dimNoua)
{
    this->dim = dimNoua;
}

void Joc::setTabla(const string& tablaNoua)
{
    this->tabla = tablaNoua;
}

void Joc::setJucator(const char& jucatorNou)
{
    this->jucator = jucatorNou;
}

void Joc::setStare(const string& stareNoua)
{
    this->stare = stareNoua;
}
