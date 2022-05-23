#pragma once
#include "Validator.h"
#include "Task.h"
#include "Repository.h"
#include "Observer.h"

class Service :public Observable
{
private:
	Repo& r;
	Valid& v;
public:
	Service(Repo& r, Valid& v) :r{ r }, v{ v }{}

	// valideaza campurile unui task si il adauga
	// se arunca exceptii de la validator si de la repository
	void addTask(const int& id, const string& descriere, const vector<string>& programatori, const string& stare);

	// returneaza lista de task-uri din repo
	vector<Task> getTasks();

	// sorteaza lista dupa stare
	vector<Task> sortByState();

	// cauta un task
	Task searchByID(const int& id);

	// returneaza task-urile unui programator
	vector<Task> getTasksByProg(string nume);

	// returneaza task-urile dupa stare
	vector<Task> getTasksByState(string stare);

	void modifyState(const int& id, const string& stare);
};