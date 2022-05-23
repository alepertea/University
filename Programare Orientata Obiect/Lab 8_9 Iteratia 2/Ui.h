#pragma once
#include "Medicament.h"
#include "Service.h"

class ConsoleUI
{
private:
	Service& srv;

	/* Citeste datele de la tastatura si adauga medicament */
	void adaugaUI();

	/* Tipareste lista de medicamente */
	void printUI(const vector<Medicament>& meds);

	/* Modifica pretul si substanta unui medicament daca exista */
	void modificaUI();

	/* Cauta un medicament dupa denumire si producator */
	void cautaUI();

	/* Sterge medicamentul dupa denumire si producator daca exista */
	void stergeUI();

	/* Cere criteriu de filtrare de la utilizator si afiseaza medicamentele cu valori mai mici in functie de criteriu */
	void filtreazaUI();

	/* Sorteaza un vector de medicamente */
	void sorteazaUI();

	/* Adauga medicamente generate aleator */
	void randomUI();

	/* Intra in meniul pentru reteta */
	void retetaUI();

	/* Cere numele fisierului CSV si afiseaza reteta */
	void uiExportCSV();

	/* Cere numele fisierului HTML si afiseaza reteta  */
	void uiExportHTML();

	/* Face undo la ultima operatie efectuata */
	void UndoUI();

	void statisticaUI();

public:
	ConsoleUI(Service& srv) :srv{ srv } {}

	ConsoleUI(const ConsoleUI& ot) = delete;

	int start();
};