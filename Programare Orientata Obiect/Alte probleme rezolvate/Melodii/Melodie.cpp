#include "Melodie.h"

int Melodie::getID() const
{
    return this->id;
}

string Melodie::getTitlu() const
{
    return this->titlu;
}

string Melodie::getArtist() const
{
    return this->artist;
}

int Melodie::getRank() const
{
    return this->rank;
}

void Melodie::setRank(const int& value)
{
    this->rank = value;
}

void Melodie::setTitle(const string& value)
{
    this->titlu = value;
}
