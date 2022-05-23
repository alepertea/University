#include "Validator.h"

string ValidException::getMessage() const
{
    return this->msg;
}

void Valid::validate(const Joc& j)
{
    int dim = j.getDim();
    string tabla = j.getTabla();
    char jucator = j.getJucator();
    string stare = j.getStare();

    if (dim != 3 && dim != 4 && dim != 5)
        throw ValidException("Dimensiune invalida");
    if (tabla.size() != dim * dim)
        throw ValidException("Dimensiune tabla invalida");
    for (unsigned int i = 0; i < tabla.size(); i++)
        if (tabla[i] != 'X' && tabla[i] != 'O' && tabla[i] != '-')
            throw ValidException("Tabla invalida");
    if (jucator != 'X' && jucator != 'O')
        throw ValidException("Jucator invalid");
    if (stare != "Neinceput" && stare != "InDerulare" && stare != "Terminat")
        throw ValidException("Stare invalida");
}
