#pragma once
#include "participant.h"

typedef struct
{
	Participant* participanti;
	int lungime;
	int capacitate;
}Vector;

typedef struct
{
	Vector* v;
	int len;
	int cp;
}UndoList;

Vector* creareVector();

UndoList* creareUndoList();

void distrugeVector(Vector* v);