#pragma once
#include "Medicament.h"
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class ValidateException
{
private:
	vector<string> msgs;

public:
	ValidateException(const vector<string>& errors) :msgs{ errors } {}
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class Validator
{
public:
	/*
		Valideaza campurile introduse de utilizator
	*/
	void validate(const Medicament& m);
};