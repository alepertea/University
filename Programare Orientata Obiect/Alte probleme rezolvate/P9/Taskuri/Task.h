#pragma once
#include <string>
#include <vector>

using namespace std;

class Task
{
private:
	int id;
	string descriere;
	string stare;	// poate fi doar open, inprogress, closed
	vector<string> programatori;
public:
	Task(const int& id, const string& descriere, const vector<string>& programatori, const string& stare) :id{ id }, descriere{ descriere }, stare{ stare }, programatori{ programatori }{}

	// Getters
	int getID() const;
	string getDescriere() const;
	string getStare() const;
	vector<string> getProgramatori() const;

	void setStare(const string& newState);
	void setProgramatori(const string& newProgrammer);
};