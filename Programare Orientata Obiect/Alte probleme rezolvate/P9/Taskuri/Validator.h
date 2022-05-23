#pragma once
#include "Task.h"

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

	// valideaza campurile unui task
	// arunca exceptii daca vede un camp invalid
	void validate(Task t);
};