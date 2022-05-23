#pragma once
#include "Joc.h"

class ValidException
{
private:
	string msg;
public:
	ValidException(const string& msg) :msg{ msg } {}
	string getMessage() const;
};

class Valid
{
public:
	Valid() = default;

	// valideaza campurile unui joc
	// arunca exceptie daca gaseste un camp invalid
	void validate(const Joc& j);
};