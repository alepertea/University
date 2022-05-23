#include "Service.h"

void Service::addTask(const int& id, const string& descriere, const vector<string>& programatori, const string& stare)
{
	Task t{ id, descriere, programatori, stare };
	this->v.validate(t);
	this->r.add(t);
	notify();
}

vector<Task> Service::getTasks()
{
	return this->r.getAll();
}

vector<Task> Service::sortByState()
{
	vector<Task> rez = this->getTasks();
	for (int i = 0; i < rez.size() - 1; i++)
		for (int j = i + 1; j < rez.size(); j++)
			if (rez[i].getStare() > rez[j].getStare())
			{
				Task aux = rez[i];
				rez[i] = rez[j];
				rez[j] = aux;
			}
	return rez;
}

Task Service::searchByID(const int& id)
{
	return this->r.search(id);
}

vector<Task> Service::getTasksByProg(string nume)
{
	return this->r.getTasksByProg(nume);
}

vector<Task> Service::getTasksByState(string stare)
{
	return this->r.getTasksByState(stare);
}

void Service::modifyState(const int& id, const string& stare)
{
	this->r.modify(id, stare);
	notify();
}
