#include <stdio.h>
#include <string.h>

int validareParticipant(char* nume, char* prenume, int scor)
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

	if (strcmp(nume, "") == 0 || strcmp(nume, " ") == 0)
		return 1;

	if (strcmp(prenume, "") == 0 || strcmp(prenume, " ") == 0)
		return 2;

	if (scor < 10 || scor > 100)
		return 3;

	int i;
	for (i = 0; i < strlen(nume); i++)
		if (strchr("0123456789", nume[i]) != NULL)
			return 1;
	for (i = 0; i < strlen(prenume); i++)
		if (strchr("0123456789", prenume[i]) != NULL)
			return 2;
	return 0;
}