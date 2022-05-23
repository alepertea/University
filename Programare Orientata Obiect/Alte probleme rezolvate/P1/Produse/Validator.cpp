#include "Validator.h"

int Valid::validate(const Produs& p)
{
    int errorCode = 1;
    if (p.getNume() == "")
        errorCode *= 2;
    if (p.getPret() < 1 || p.getPret() > 100)
        errorCode *= 3;
    if (errorCode != 1)
        return errorCode;
    return 0;
}