#include "DTO.h"

int DTO::getSubstantaActiva() const
{
    return this->substantaActiva;
}

int DTO::getNrMedicamente() const
{
    return this->nrMedicamente;
}

void DTO::setNrMedicamente(int value)
{
    this->nrMedicamente = value;
}
