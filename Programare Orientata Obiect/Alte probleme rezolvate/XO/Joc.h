#pragma once
#include <string>

using namespace std;

class Joc
{
private:
	int id;
	int dim;
	string tabla;
	char jucator;
	string stare;

public:
	Joc(const int& i, const int& d, const string& t, const char& j, const string& s) :id{ i }, dim{ d }, tabla{ t }, jucator{ j }, stare{ s }{}

	// Getters
	int getID() const;
	int getDim() const;
	string getTabla() const;
	char getJucator() const;
	string getStare() const;

	// Setters
	void setID(const int& idNou);
	void setDim(const int& dimNoua);
	void setTabla(const string& tablaNoua);
	void setJucator(const char& jucatorNou);
	void setStare(const string& stareNoua);
};