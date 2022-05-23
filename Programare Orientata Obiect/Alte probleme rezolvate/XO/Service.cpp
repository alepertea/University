#include "Service.h"

void Service::add(const int& id, const int& dim, const string& tabla, const char& jucator, const string& stare)
{
	Joc j{ id, dim, tabla, jucator, stare };
	this->v.validate(j);
	this->r.add(j);
}

void Service::modify(const int& id, const int& dim, const string& tabla, const char& jucator, const string& stare)
{
	Joc j{ id, dim, tabla, jucator, stare };
	this->v.validate(j);
	this->r.modify(id, dim, tabla, jucator, stare);
}

vector<Joc> Service::getAll()
{
	vector<Joc> all = this->r.getAll();
	sort(all.begin(), all.end(), [&](Joc j1, Joc j2) {return j1.getStare() < j2.getStare(); });
	return all;
}
