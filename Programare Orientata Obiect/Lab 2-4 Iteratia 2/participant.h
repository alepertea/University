#pragma once

typedef struct
{
	char* nume;
	char* prenume;
	int scor;
}Participant;

Participant creareParticipant(char* nume, char* prenume, int scor);

void distrugeParticipant(Participant* p);

char* getNume(Participant* p);

char* getPrenume(Participant* p);

int getScor(Participant* p);