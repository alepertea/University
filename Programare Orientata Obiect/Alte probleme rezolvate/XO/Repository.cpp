#include "Repository.h"

void Repo::loadFromFile()
{
    ifstream fin(this->filename);
    if (!fin.is_open())
        return;

    int id, dim;
    string tabla, stare;
    char jucator;
    while (!fin.eof())
    {
        fin >> id >> dim >> tabla >> jucator >> stare;
        if (fin.eof())
            break;
        Joc j{ id, dim, tabla, jucator, stare };
        this->add(j);
    }
    fin.close();
}

void Repo::storeToFile()
{
    ofstream fout(this->filename);
    if (!fout.is_open())
        return;
    for (const auto& j : this->jocuri)
    {
        fout << j.getID() << " " << j.getDim() << " " << j.getTabla() << " " << j.getJucator() << " " << j.getStare() << "\n";
    }
    fout.close();
}

bool Repo::exist(const Joc& j)
{
    for (const auto& joc : this->jocuri)
        if (joc.getID() == j.getID())
            return true;
    return false;
}

void Repo::add(Joc j)
{
    while (exist(j))
        j.setID(rand());
    this->jocuri.push_back(j);
    this->storeToFile();
}

void Repo::modify(const int& id, const int& dim, const string& tabla, const char& jucator, const string& stare)
{
    for(auto& joc : this->jocuri)
        if (joc.getID() == id)
        {
            joc.setDim(dim);
            joc.setTabla(tabla);
            joc.setJucator(jucator);
            joc.setStare(stare);
        }
    this->storeToFile();
}

vector<Joc> Repo::getAll()
{
    return this->jocuri;
}
