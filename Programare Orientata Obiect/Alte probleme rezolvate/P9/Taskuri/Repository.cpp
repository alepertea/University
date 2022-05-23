#include "Repository.h"

string RepoException::getMessage() const
{
    return this->msg;
}

void Repo::loadFromFile()
{
    ifstream fin(this->filename);

    if (!fin.is_open())
        throw RepoException("Eroare la deschiderea fisierului");

    int id;
    string descriere, stare, aux;
    vector<string> programatori;
    while (!fin.eof())
    {
        fin >> id;
        fin >> descriere;
        fin >> stare;
        fin >> aux;
        programatori.clear();
        programatori.push_back(aux);

        if (fin.eof())
            break;

        Task t{ id, descriere, programatori, stare };
        this->add(t);
    }

    fin.close();
}

void Repo::storeToFile()
{
    ofstream fout(this->filename);

    if (!fout.is_open())
        throw RepoException("Eroare la deschiderea fisierului");

    for (const auto& t : this->tasks)
    {
        for (const auto& p : t.getProgramatori())
        {
            fout << t.getID() << "\n";
            fout << t.getDescriere() << "\n";
            fout << t.getStare() << "\n";
            fout << p << "\n";
        }
    }

    fout.close();
}

bool Repo::exist(Task t)
{
    for (const auto& task : this->tasks)
        if (t.getID() == task.getID())
            return true;
    return false;
}

int Repo::getPozitie(Task t)
{
    int poz = 0;
    for (const auto& task : this->tasks)
    {
        if (task.getID() == t.getID())
            break;
        poz++;
    }
    if (poz == this->tasks.size())
        return -1;
    return poz;
}

void Repo::add(Task t)
{
    for (const auto& task : this->tasks)
        if (task.getID() == t.getID())
            if (task.getProgramatori().size() == 4)
                throw RepoException("ID existent");
    int poz = this->getPozitie(t);
    if (poz == -1)
        this->tasks.push_back(t);
    else
        this->tasks[poz].setProgramatori(t.getProgramatori()[0]);
    this->storeToFile();
}

vector<Task> Repo::getAll()
{
    return this->tasks;
}

Task Repo::search(const int& id)
{
    for (const auto& t : this->tasks)
        if (t.getID() == id)
            return t;
    throw RepoException("Task-ul nu exista");
}

vector<Task> Repo::getTasksByProg(const string& nume)
{
    vector<Task> rez;
    for (const auto& t : this->tasks)
        for(const auto& p : t.getProgramatori())
            if (p.find(nume) != string::npos)
            {
                rez.push_back(t);
                break;
            }
    return rez;
}

vector<Task> Repo::getTasksByState(const string& stare)
{
    vector<Task> rez;
    for (const auto& t : this->tasks)
        if (t.getStare() == stare)
            rez.push_back(t);
    return rez;
}

void Repo::modify(const int& id, const string& stare)
{
    for (auto& t : this->tasks)
        if (t.getID() == id)
            t.setStare(stare);
    this->storeToFile();
}
