#pragma once

typedef struct
{
	char nume[20];
	char prenume[20];
	int scor;
}Participant;

Participant p[31];
int len;

void initializare();