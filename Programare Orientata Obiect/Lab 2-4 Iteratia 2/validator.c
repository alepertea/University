#include "participant.h"
#include <string.h>

int valideazaParticipant(Participant p)
{
	/*
		Verifica daca datele introduse de utilizator sunt valide.
		Input: nume, prenume - string
			   scor - int
		Output: - 1, daca numele este invalid, adica: sirul este vid, este doar un spatiu sau stringul contine cifre
				- 2, daca prenumele este invalid, adica: sirul este vid, este doar un spatiu sau stringul contine cifre
				- 3, daca scorul este invalid, adica nu este o valoare din intervalul [10, 100]
				- 0, daca datele sunt valide
	*/

	if (strcmp(p.nume, "") == 0 || strcmp(p.nume, " ") == 0)
		return 1;

	if (strcmp(p.prenume, "") == 0 || strcmp(p.prenume, " ") == 0)
		return 2;

	if (p.scor < 10 || p.scor > 100)
		return 3;

	unsigned int i;
	for (i = 0; i < strlen(p.nume); i++)
		if (strchr("0123456789", p.nume[i]) != NULL)
			return 1;
	for (i = 0; i < strlen(p.prenume); i++)
		if (strchr("0123456789", p.prenume[i]) != NULL)
			return 2;

	return 0;
}