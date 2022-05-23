#pragma once
#include "Produs.h"

class Valid
{
public:
	Valid() = default;

	// valideaza un produs si returneaza niste coduri de eroare:
	//		- errorCode = 0 --> produsul e valid
	//		- errorCode = 2 --> nume invalid
	//		- errorCode = 3 --> pret invalid
	//		- errorCode = 6 --> nume si pret invalide
	int validate(const Produs& p);
};