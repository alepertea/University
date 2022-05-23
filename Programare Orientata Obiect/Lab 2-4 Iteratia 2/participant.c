#include "participant.h"
#include <stdlib.h>
#include <string.h>

Participant creareParticipant(char* nume, char* prenume, int scor)
{
	Participant rez;
	int nrC = strlen(nume) + 1;
	rez.nume = (char*)malloc(nrC);
	if(rez.nume)
		strcpy_s(rez.nume, nrC, nume);

	nrC = strlen(prenume) + 1;
	rez.prenume = (char*)malloc(nrC);
	if(rez.prenume)
		strcpy_s(rez.prenume, nrC, prenume);

	rez.scor = scor;

	return rez;
}

void distrugeParticipant(Participant* p)
{
	free(p->nume);
	free(p->prenume);
	p->nume = NULL;
	p->prenume = NULL;
	p->scor = 0;
}

char* getNume(Participant* p)
{
	return p->nume;
}

char* getPrenume(Participant* p)
{
	return p->prenume;
}

int getScor(Participant* p)
{
	return p->scor;
}