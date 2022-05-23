#include "Service.h"

int Service::addProduct(const int& id, const string& nume, const string& tip, const double& pret)
{
    Produs p{ id, nume, tip, pret };
    int errorCode = this->v.validate(p);
    int ok = 0;
    if (errorCode == 0)
        ok = this->r.add(p);
    notify();
    if (ok == 1)
        return ok;
    return errorCode;
}

vector<Produs> Service::getProducts()
{
    return this->r.getAll();
}

vector<Produs> Service::sortByPrice()
{
    vector<Produs> rez = r.getAll();
    for (unsigned int i = 0; i < rez.size() - 1; i++)
        for (unsigned int j = i + 1; j < rez.size(); j++)
            if (rez[i].getPret() > rez[j].getPret())
            {
                Produs aux = rez[i];
                rez[i] = rez[j];
                rez[j] = aux;
            }
    return rez;
}

vector<Produs> Service::filterProducts(const double& pret)
{
    vector<Produs> rez;
    vector<Produs> all = this->r.getAll();

    for (const auto& p : all)
        if (p.getPret() < pret)
            rez.push_back(p);
    return rez;
}

int Service::getNumberOfProducts(const string& tip)
{
    return this->r.getNumberOfProducts(tip);
}