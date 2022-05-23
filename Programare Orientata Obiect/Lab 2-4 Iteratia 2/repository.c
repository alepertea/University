#include "repository.h"
#include "vectordinamic.h"
#include "participant.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int cauta(Repo* r, char* num, char* prenum)
{
	/*
		Verifica daca exista participant cu un nume si prenume dat
		Input: num, prenum - string
		Output: - 0, daca nu se gaseste participantul
				- pozitia lui in sir, altfel
	*/

	int i;
	for (i = 0; i < r->elems->lungime; i++)
		if (strcmp(r->elems->participanti[i].nume, num) == 0 && strcmp(r->elems->participanti[i].prenume, prenum) == 0)
			return i;
	return -1;
}

int addParticipant(Repo* r, Participant* p)
{
	/*
		Adauga adresa unui participant la vectorul dinamic
	*/

	if (r->elems->lungime == r->elems->capacitate)
	{
		//redimensionare
		int newCap = r->elems->capacitate * 2;
		Repo* vnou = (Repo*)malloc(newCap * sizeof(Repo*));
		if (vnou)
		{
			int i;
			for (i = 0; i < r->elems->lungime; i++)
				vnou->elems->participanti[i] = r->elems->participanti[i];
			free(r);
			r = vnou;
			if (r)
			{
				r->elems->capacitate = newCap;
				r->elems->lungime = newCap / 2 - 1;
			}
		}
	}

	int c = cauta(r, p->nume, p->prenume);
	if (c != -1)
		return 4;

	if (r)
	{
		r->elems->participanti[r->elems->lungime] = *p;
		r->elems->lungime++;
	}
	
	return 0;
}

int actualizeazaParticipant(Repo* r, Participant* p, int scor)
{
	/*
		Modifica scorul participantului dat.
		Input: p - participant
			   scor - int
		Output: 4, daca nu exista participantul cu datele introduse
				0 si se modifica participantul, altfel
	*/

	int c = cauta(r, p->nume, p->prenume);
	if (c == -1)
		return 4;
	r->elems->participanti[c].scor = scor;
	return 0;
}

int stergeParticipant(Repo* r, Participant* p)
{
	/*
		Sterge participantul dat.
		Input: p - participant
		Output: 1, daca nu exista participantul cu datele introduse
				0 si se sterge participantul, altfel
	*/

	int c = cauta(r, p->nume, p->prenume);
	if (c == -1)
		return 4;
	int i;
	for (i = c; i < r->elems->lungime - 1; i++)
	{
		Participant aux = r->elems->participanti[i];
		r->elems->participanti[i] = r->elems->participanti[i + 1];
		r->elems->participanti[i + 1] = aux;
	}		
	distrugeParticipant(&r->elems->participanti[i]);
	r->elems->lungime--;
	return 0;
}

int filtreazaValoare(Repo* r, int val)
{
	/*
		Afiseaza participantii care au scorul mai mic decat o valoare data.
		Input: val - int
		Output: 0 si se afiseaza, daca exista participanti care indeplinesc criteriul
				1, altfel
	*/

	int i, ok = 1;

	for (i = 0; i < r->elems->lungime; i++)
		if (r->elems->participanti[i].scor < val)
		{
			printf("%s %s %d \n", r->elems->participanti[i].nume, r->elems->participanti[i].prenume, r->elems->participanti[i].scor);
			ok = 0;
		}

	return ok;
}

int afiseazaParticipanti(Repo* r)
{
	int i, ok = 1;
	for (i = 0; i < r->elems->lungime; i++)
	{
		ok = 0;
		printf("%s %s %d \n", r->elems->participanti[i].nume, r->elems->participanti[i].prenume, r->elems->participanti[i].scor);
	}
	return ok;
}

int filtreazaLitera(Repo* r, char* lit)
{
	/*
		Afiseaza participantii care au numele care incepe cu litera data.
		Input: lit - string
		Output: 0 si se afiseaza, daca exista participanti
				1, altfel
	*/

	int i, ok = 1;

	for (i = 0; i < r->elems->lungime; i++)
		if (r->elems->participanti[i].nume[0] == lit[0])
		{
			printf("%s %s %d \n", r->elems->participanti[i].nume, r->elems->participanti[i].prenume, r->elems->participanti[i].scor);
			ok = 0;
		}

	return ok;
}

int sorteazaCrescatorNume(Repo* r)
{
	/*
		Sorteaza crescator dupa nume sirul de participanti.
		Input: -
		Output: 0, daca sirul nu era ordonat inainte
				1, daca sirul era deja ordonat
	*/

	int i, j, ok = 1;
	for (i = 0; i < r->elems->lungime; i++)
		for (j = i + 1; j < r->elems->lungime; j++)
			if (strcmp(r->elems->participanti[i].nume, r->elems->participanti[j].nume) > 0)
			{
				Participant aux = r->elems->participanti[i];
				r->elems->participanti[i] = r->elems->participanti[j];
				r->elems->participanti[j] = aux;
				ok = 0;
			}
	return ok;
}

int sorteazaDescrescatorNume(Repo* r)
{
	/*
		Sorteaza descrescator dupa nume sirul de participanti.
		Input: -
		Output: 0, daca sirul nu era ordonat inainte
				1, daca sirul era deja ordonat
	*/

	int i, j, ok = 1;
	for (i = 0; i < r->elems->lungime; i++)
		for (j = i + 1; j < r->elems->lungime; j++)
			if (strcmp(r->elems->participanti[i].nume, r->elems->participanti[j].nume) < 0)
			{
				Participant aux = r->elems->participanti[i];
				r->elems->participanti[i] = r->elems->participanti[j];
				r->elems->participanti[j] = aux;
				ok = 0;
			}
	return ok;
}

int sorteazaCrescatorScor(Repo* r)
{
	/*
		Sorteaza crescator dupa scor sirul de participanti.
		Input: -
		Output: 0, daca sirul nu era ordonat inainte
				1, daca sirul era deja ordonat
	*/

	int i, j, ok = 1;
	for (i = 0; i < r->elems->lungime; i++)
		for (j = i + 1; j < r->elems->lungime; j++)
			if (r->elems->participanti[i].scor > r->elems->participanti[j].scor)
			{
				Participant aux = r->elems->participanti[i];
				r->elems->participanti[i] = r->elems->participanti[j];
				r->elems->participanti[j] = aux;
				ok = 0;
			}
	return ok;
}

int sorteazaDescrescatorScor(Repo* r)
{
	/*
		Sorteaza descrescator dupa scor sirul de participanti.
		Input: -
		Output: 0, daca sirul nu era ordonat inainte
				1, daca sirul era deja ordonat
	*/

	int i, j, ok = 1;
	for (i = 0; i < r->elems->lungime; i++)
		for (j = i + 1; j < r->elems->lungime; j++)
			if (r->elems->participanti[i].scor < r->elems->participanti[j].scor)
			{
				Participant aux = r->elems->participanti[i];
				r->elems->participanti[i] = r->elems->participanti[j];
				r->elems->participanti[j] = aux;
				ok = 0;
			}
	return ok;
}