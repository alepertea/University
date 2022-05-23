#pragma once
#include <string>

using namespace std;

class Produs
{
private:
	int id;
	string nume;
	string tip;
	double pret;

public:
	Produs(const int& id, const string& nume, const string& tip, const double& pret) : id{ id }, nume{ nume }, tip{ tip }, pret{ pret }{}

	int getID() const;
	string getNume() const;
	string getTip() const;
	double getPret() const;
	int getNumarVocale() const;
};