#include "vectordinamic.h"
#include "participant.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

Vector* creareVector()
{
	Vector* v = (Vector*)malloc(sizeof(Vector));
	if (v)
	{
		v->capacitate = 10;
		v->lungime = 0;
		v->participanti = (Participant*)malloc(v->capacitate * sizeof(Participant));
		return v;
	}
	Vector* vNull = NULL;
	return vNull;
}

UndoList* creareUndoList()
{
	UndoList* u = (UndoList*)malloc(sizeof(UndoList));
	if (u)
	{
		u->cp = 50;
		u->len = 0;
		u->v->participanti = (Participant*)malloc(u->v->capacitate * sizeof(Participant));
		return u;
	}
	UndoList* uNull = NULL;
	return uNull;
}

void distrugeVector(Vector* v)
{
	int i;
	for (i = 0; i < v->lungime; i++)
	{
		Participant p = v->participanti[i];
		distrugeParticipant(&p);
	}
	v->lungime = 0;
	free(v->participanti);
	v->participanti = NULL;
}

