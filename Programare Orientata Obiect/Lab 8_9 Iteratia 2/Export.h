#pragma once
#include "Medicament.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/*
	Scrie in fisier CSV reteta de medicamente
	Arunca exceptie daca nu poate crea fisierul
*/
void exportToCSV(const string& filename, const vector<Medicament>& meds);

/*
	Scrie in fisier HTML reteta de medicamente
	Arunca exceptie daca nu poate crea fisierul
*/
void exportToHTML(const string& filename, const vector<Medicament>& meds);