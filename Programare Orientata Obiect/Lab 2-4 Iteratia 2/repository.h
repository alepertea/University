#pragma once
#include "vectordinamic.h"

typedef struct
{
	Vector* elems;
}Repo;

int addParticipant(Repo* r, Participant* p);

int cauta(Repo* r, char* num, char* prenum);

int actualizeazaParticipant(Repo* r, Participant* p, int scor);

int stergeParticipant(Repo* r, Participant* p);

int filtreazaValoare(Repo* r, int val);

int filtreazaLitera(Repo* r, char* lit);

int sorteazaCrescatorNume(Repo* r);

int sorteazaDescrescatorNume(Repo* r);

int sorteazaCrescatorScor(Repo* r);

int sorteazaDescrescatorScor(Repo* r);

int afiseazaParticipanti(Repo* r);