#pragma once
#include "Task.h"
#include <vector>
#include <fstream>

using namespace std;

class RepoException
{
private:
	string msg;
public:
	RepoException(const string& msg) :msg{ msg } {}
	string getMessage() const;
};

class Repo
{
private:
	// lista de task-uri
	vector<Task> tasks;

	// numele fisierului de unde citim task-urile
	string filename;

	// incarca datele in fisier
	void loadFromFile();

	// citeste datele din fisier si le stocheaza in lista de task-uri
	void storeToFile();

	// functie care determina daca exista un task in lista
	// verifica id-urile
	bool exist(Task t);

	int getPozitie(Task t);

public:
	Repo(const string& filename) :filename{ filename } { this->loadFromFile(); }

	// adauga un task in lista
	// daca id-ul exista deja, arunca exceptie si nu mai adauga task-ul
	void add(Task t);

	// returneaza lista de task-uri
	vector<Task> getAll();

	// returneaza un task dupa id-ul lui
	// arunca exceptie daca nu exista
	Task search(const int& id);

	// returneaza toate task-urile unui programator
	vector<Task> getTasksByProg(const string& nume);

	// returneaza toate task-urile dupa stare
	vector<Task> getTasksByState(const string& stare);

	void modify(const int& id, const string& stare);
};