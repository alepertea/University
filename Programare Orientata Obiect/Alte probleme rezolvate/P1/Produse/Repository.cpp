#include "Repository.h"

void Repo::loadFromFile()
{
    ifstream fin(this->filename);

    if (!fin.is_open())
        return;

    int id;
    string nume, tip;
    double pret;
    while (!fin.eof())
    {
        fin >> id;
        fin >> nume;
        fin >> tip;
        fin >> pret;

        if (fin.eof())
            break;

        Produs p{ id, nume, tip, pret };
        this->add(p);
    }

    fin.close();
}

void Repo::storeToFile()
{
    ofstream fout(this->filename);

    if (!fout.is_open())
        return;

    for (const auto& p : this->produse)
    {
        fout << p.getID() << "\n";
        fout << p.getNume() << "\n";
        fout << p.getTip() << "\n";
        fout << p.getPret() << "\n";
    }

    fout.close();
}

bool Repo::exist(const Produs& p)
{
    for (const auto& produs : this->produse)
        if (produs.getID() == p.getID())
            return true;
    return false;
}

int Repo::add(const Produs& p)
{
    if (exist(p))
        return 1;
    this->produse.push_back(p);
    this->storeToFile();
    return 0;
}

vector<Produs> Repo::getAll()
{
    return this->produse;
}

int Repo::getNumberOfProducts(const string& tip)
{
    int count = 0;
    for (const auto& p : this->getAll())
        if (p.getTip() == tip)
            count++;
    return count;
}