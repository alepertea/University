#include <stdio.h>
#include "validari.h"
#include "repository.h"

void adaugareParticipant(char* nume, char* prenume, int scor)
{
	/*
		Valideaza datele introduse si daca sunt valide apeleaza functia din repo
		Input: nume, prenume - string
			   scor - int
		Output: mesaje in cazul in care datele sunt invalide
	*/

	int v = validareParticipant(nume, prenume, scor);

	if (v == 1)
		printf("Nume invalid. \n");

	if (v == 2)
		printf("Prenume invalid. \n");

	if (v == 3)
		printf("Scor invalid. \n");

	if (v == 0)
		adaugaParticipant(nume, prenume, scor);
}

void afisareParticipanti()
{
	/*
		Apeleaza functia din repo pentru afisare
		Input: -
		Output: -
	*/
	afiseazaParticipanti();
}

void actualizareParticipant(char* num, char* prenum, int s)
{
	/*
		Valideaza datele introduse si daca sunt valide apeleaza functia din repo
		Input: num, prenum - string
			   s - int
		Output: mesaje in cazul in care datele sunt invalide
	*/

	int v = validareParticipant(num, prenum, s);

	if (v == 1)
		printf("Nume invalid. \n");

	if (v == 2)
		printf("Prenume invalid. \n");

	if (v == 3)
		printf("Scor invalid. \n");

	int act;
	if (v == 0)
		act = actualizeazaParticipant(num, prenum, s);
}

void stergereParticipant(char* num, char* prenum)
{
	/*
		Valideaza datele introduse si daca sunt valide apeleaza functia din repo
		Input: num, prenum - string
		Output: mesaje in cazul in care datele sunt invalide
	*/

	int v = validareParticipant(num, prenum, 50);

	if (v == 1)
		printf("Nume invalid. \n");

	if (v == 2)
		printf("Prenume invalid. \n");

	int st;
	if (v == 0)
		st = stergeParticipant(num, prenum);
}

void filtrareValoare(int val)
{
	/*
		Apeleaza functia din repo pentru filtrare in functie de valoare
		Input: -
		Output: -
	*/

	filtreazaValoare(val);
}

void filtrareLitera(char* lit)
{
	/*
		Apeleaza functia din repo pentru filtrare in functie de prima litera din nume
		Input: -
		Output: -
	*/

	filtreazaLitera(lit);
}

void sortareCrescatorNume()
{
	/*
		Apeleaza functia din repo pentru sortare crescatoare dupa nume
		Input: -
		Output: -
	*/

	sorteazaCrescatorNume();
}

void sortareDescrescatorNume()
{
	/*
		Apeleaza functia din repo pentru sortare descrescatoare dupa nume
		Input: -
		Output: -
	*/

	sorteazaDescrescatorNume();
}

void sortareCrescatorScor()
{
	/*
		Apeleaza functia din repo pentru sortare crescatoare dupa scor
		Input: -
		Output: -
	*/

	sorteazaCrescatorScor();
}

void sortareDescrescatorScor()
{
	/*
		Apeleaza functia din repo pentru sortare descrescatoare dupa scor
		Input: -
		Output: -
	*/

	sorteazaDescrescatorScor();
}