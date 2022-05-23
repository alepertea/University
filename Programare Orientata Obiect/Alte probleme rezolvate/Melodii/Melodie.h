#pragma once
#include <string>
#include <vector>

using namespace std;

class Melodie
{
private:
	int id;		// unic
	string titlu;
	string artist;
	int rank;	// intre 0 si 100

public:
	Melodie(const int& id, const string& titlu, const string& artist, const int& rank) :id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank }{}

	int getID() const;
	string getTitlu() const;
	string getArtist() const;
	int getRank() const;

	void setRank(const int& value);
	void setTitle(const string& value);
};