#pragma once
#include "repository.h"
#include "validator.h"

typedef struct
{
	Repo* r;
}Srv;

int adaugareParticipant(Srv* s, char* nume, char* prenume, int scor);

int afisareParticipanti(Srv* s);

int actualizareParticipant(Srv* s, char* nume, char* prenume, int scor);

int stergereParticipant(Srv* s, char* nume, char* prenume);

int filtrareValoare(Srv* s, int val);

int filtrareLitera(Srv* s, char* lit);

int sortareCrescatorNume(Srv* s);

int sortareDescrescatorNume(Srv* s);

int sortareCrescatorScor(Srv* s);

int sortareDescrescatorScor(Srv* s);