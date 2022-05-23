#include "Repository.h"

void Repo::loadFromFile()
{
    ifstream fin(this->filename);

    if (!fin.is_open())
        throw RepoException("Eroare la deschiderea fisierului");

    int id, rank;
    string titlu, artist;
    while (!fin.eof())
    {
        fin >> id;
        fin >> titlu;
        fin >> artist;
        fin >> rank;

        if (fin.eof())
            break;

        Melodie m{ id, titlu, artist, rank };
        this->add(m);
    }

    fin.close();
}

void Repo::storeToFile()
{
    ofstream fout(this->filename);

    if (!fout.is_open())
        throw RepoException("Eroare la deschiderea fisierului");

    for (const auto& m : this->songs)
    {
        fout << m.getID() << "\n";
        fout << m.getTitlu() << "\n";
        fout << m.getArtist() << "\n";
        fout << m.getRank() << "\n";
    }

    fout.close();
}

bool Repo::exist(const Melodie& m)
{
    for (const auto& mel : this->songs)
        if (mel.getID() == m.getID())
            return true;
    return false;
}

int Repo::getPozitie(const Melodie& m)
{
    int poz = 0;
    for (const auto& mel : this->songs)
    {
        if (mel.getID() == m.getID())
            break;
        poz++;
    }
    return poz;
}

void Repo::add(const Melodie& m)
{
    this->songs.push_back(m);
}

void Repo::modify(const int& id, const string& titlu, const int& rank)
{
    for (auto& m : this->songs)
        if (m.getID() == id)
        {
            m.setRank(rank);
            m.setTitle(titlu);
        }
    this->storeToFile();
}

vector<Melodie> Repo::getAll()
{
    return this->songs;
}

void Repo::del(const Melodie& m)
{
    int poz = getPozitie(m);

    bool gasit = false;
    for (const auto& mel : this->songs)
    {
        if (mel.getArtist() == m.getArtist() && mel.getID() != m.getID())
            gasit = true;
    }

    if (gasit == false)
        throw RepoException("Aceasta e ultima melodie a artistului :(");

    this->songs.erase(this->songs.begin() + poz);
    this->storeToFile();
}

int Repo::getNumberOfSongsByRank(const int& rank)
{
    int count = 0;
    for (const auto& m : this->songs)
        if (m.getRank() == rank)
            count++;
    return count;
}

string RepoException::getMessage() const
{
    return this->msg;
}
