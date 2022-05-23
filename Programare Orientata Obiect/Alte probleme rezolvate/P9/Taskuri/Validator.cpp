#include "Validator.h"

string ValidException::getMessage() const
{
    return this->msg;
}

void Valid::validate(Task t)
{
    if (t.getDescriere() == "")
        throw ValidException("Descriere invalida");
    string stare = t.getStare();
    if (stare != "open" && stare != "inprogress" && stare != "closed")
        throw ValidException("Stare invalida");
    if (t.getProgramatori().size() < 1 || t.getProgramatori().size() > 4)
        throw ValidException("Numar de programatori invalid");
}
