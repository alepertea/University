#include "service.h"
#include "repository.h"
#include "validator.h"
#include "participant.h"
#include <assert.h>

int adaugareParticipant(Srv* s, char* nume, char* prenume, int scor)
{
	/*
		Creeaza un participant nou si il valideaza.
		Daca nu trece de validari, il distrugem, incercam sa il stergem.
		Daca nu exista deja participant cu acelasi nume si prenume, il distrugem.

		Input: nume, prenume - string
			   scor - int
		Output: v sau c - cod de eroare
	*/
	Participant p = creareParticipant(nume, prenume, scor);
	int v = valideazaParticipant(p);
	if (v != 0)
	{
		distrugeParticipant(&p);
		return v;
	}
	int c = addParticipant(s->r, &p);
	if (c == 4)
		distrugeParticipant(&p);
	return c;
}

int afisareParticipanti(Srv* s)
{
	/*
		Apeleaza functia din repository pentru afisare.
	*/
	int ok = afiseazaParticipanti(s->r);
	return ok;
}

int actualizareParticipant(Srv* s, char* nume, char* prenume, int scor)
{
	/*
		Creeaza un participant nou si il valideaza.
		Daca nu trece de validari, il distrugem, incercam sa il stergem.
		Daca nu exista participant de actualizat, il distrugem.

		Input: nume, prenume - string
			   scor - int
		Output: v sau c - cod de eroare
	*/
	Participant p = creareParticipant(nume, prenume, 50);
	int v = valideazaParticipant(p);
	if (v != 0)
	{
		distrugeParticipant(&p);
		return v;
	}
	int c = actualizeazaParticipant(s->r, &p, scor);
	distrugeParticipant(&p);
	return c;
}

int stergereParticipant(Srv* s, char* nume, char* prenume)
{
	/*
		Creeaza un participant nou si il valideaza.
		Daca nu trece de validari, il distrugem, incercam sa il stergem.
		Daca nu exista participant de sters, il distrugem.

		Input: nume, prenume - string
		Output: v sau c - cod de eroare
	*/
	Participant p = creareParticipant(nume, prenume, 50);
	int v = valideazaParticipant(p);
	if (v != 0)
	{
		distrugeParticipant(&p);
		return v;
	}
	int c = stergeParticipant(s->r, &p);
	distrugeParticipant(&p);
	return c;
}

int filtrareValoare(Srv* s, int val)
{
	int ok = filtreazaValoare(s->r, val);
	return ok;
}

int filtrareLitera(Srv* s, char* lit)
{
	int ok = filtreazaLitera(s->r, lit);
	return ok;
}

int sortareCrescatorNume(Srv* s)
{
	int ok = sorteazaCrescatorNume(s->r);
	return ok;
}

int sortareDescrescatorNume(Srv* s)
{
	int ok = sorteazaDescrescatorNume(s->r);
	return ok;
}

int sortareCrescatorScor(Srv* s)
{
	int ok = sorteazaCrescatorScor(s->r);
	return ok;
}

int sortareDescrescatorScor(Srv* s)
{
	int ok = sorteazaDescrescatorScor(s->r);
	return ok;
}