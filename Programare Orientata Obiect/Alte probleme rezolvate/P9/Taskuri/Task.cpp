#include "Task.h"

int Task::getID() const
{
    return this->id;
}

string Task::getDescriere() const
{
    return this->descriere;
}

string Task::getStare() const
{
    return this->stare;
}

vector<string> Task::getProgramatori() const
{
    return this->programatori;
}

void Task::setStare(const string& newState)
{
    this->stare = newState;
}

void Task::setProgramatori(const string& newProgrammer)
{
    this->programatori.push_back(newProgrammer);
}
