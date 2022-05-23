#pragma once
#include <algorithm>
#include "Validator.h"
#include "Repository.h"
#include "Joc.h"

class Service
{
private:
	Valid& v;
	Repo& r;

public:
	Service(Repo& r, Valid& v) :r{ r }, v{ v }{}

	// valideaza campurile si adauga joc
	// arunca exceptie daca unul din campuri nu este valid
	void add(const int& id, const int& dim, const string& tabla, const char& jucator, const string& stare);

	void modify(const int& id, const int& dim, const string& tabla, const char& jucator, const string& stare);

	// returneaza lista de jocuri din repo
	// lista va fi ordonata dupa stare
	vector<Joc> getAll();
};