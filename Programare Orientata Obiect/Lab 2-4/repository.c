#include <stdio.h>
#include <string.h>
#include "domain.h"

int cauta(char* num, char* prenum)
{
	/*
		Verifica daca exista participant cu un nume si prenume dat
		Input: num, prenum - string
		Output: - 0, daca nu se gaseste participantul
				- pozitia lui in sir, altfel
	*/

	int i;
	for (i = 1; i <= len; i++)
		if (strcmp(p[i].nume, num) == 0 && strcmp(p[i].prenume, prenum) == 0)
			return i;
	return 0;
}

int adaugaParticipant(char* num, char* prenum, int s)
{
	/*
		Adauga participant in sir.
		Input: num, prenum - string
			   s - int
		Output: - 1, daca exista deja participant cu acelasi nume si prenume
				- 0 si se actualizeaza sirul, altfel
	*/

	int poz = cauta(num, prenum);
	if (poz != 0)
	{
		printf("Exista deja participant cu numele si prenumele dat. \n");
		return 1;
	}

	len++;
	int i;
	for (i = 0; i < strlen(num); i++)
		p[len].nume[i] = num[i];
	p[len].nume[i] = '\0';

	for (i = 0; i < strlen(prenum); i++)
		p[len].prenume[i] = prenum[i];
	p[len].prenume[i] = '\0';

	p[len].scor = s;

	return 0;
}

int afiseazaParticipanti()
{
	/*
		Printeaza pe ecran participantii, daca exista.
	*/

	if (len == 0)
	{
		printf("Nu exista participanti. \n");
		return 1;
	}
	else
	{
		int i;
		for (i = 1; i <= len; i++)
			printf("%s %s %d \n", p[i].nume, p[i].prenume, p[i].scor);
		return 0;
	}	
}

int actualizeazaParticipant(char* num, char* prenum, int s)
{
	/*
		Modifica scorul unui participant dat dupa nume si prenume.
		Input: num, prenum - string
			   s - int
		Output: 1, daca nu exista participant cu datele introduse
				0 si se modifica scorul, altfel
	*/

	int poz = cauta(num, prenum);
	if (poz == 0)
	{
		printf("Nu exista participantul cu numele si prenumele dat. \n");
		return 1;
	}
	else
	{
		p[poz].scor = s;
		printf("Actualizarea s-a efectuat cu succes. Apasa tasta 6 pentru a vedea lista curenta. \n");
		return 0;
	}
}

int stergeParticipant(char* num, char* prenum)
{
	/*
		Sterge participantul dat dupa nume si prenume.
		Input: num, prenum - string
		Output: 1, daca nu exista participantul cu datele introduse
				0 si se sterge participantul, altfel
	*/

	int poz = cauta(num, prenum);
	if (poz == 0)
	{
		printf("Nu exista participantul cu numele si prenumele dat. \n");
		return 1;
	}
	else
	{
		int i;
		for (i = poz + 1; i <= len; i++)
			p[i - 1] = p[i];
		len--;
		printf("Stergerea s-a efectuat cu succes. Apasa tasta 6 pentru a vedea lista curenta. \n");
		return 0;
	}
}

int filtreazaValoare(int val)
{
	/*
		Afiseaza participantii care au scorul mai mic decat o valoare data.
		Input: val - int
		Output: 0 si se afiseaza, daca exista participanti care indeplinesc criteriul
				1, altfel
	*/

	int i, ok = 1;

	for (i = 1; i <= len; i++)
		if (p[i].scor < val)
		{
			printf("%s %s %d \n", p[i].nume, p[i].prenume, p[i].scor);
			ok = 0;
		}

	if (ok == 1)
		printf("Nu exista participanti care au scor mai mic decat valoarea data. \n");

	return ok;
}

int filtreazaLitera(char* lit)
{
	/*
		Afiseaza participantii care au numele care incepe cu litera data.
		Input: lit - string
		Output: 0 si se afiseaza, daca exista participanti 
				1, altfel
	*/
	int i, ok = 1;

	for (i = 1; i <= len; i++)
		if (p[i].nume[0] == lit[0])
		{
			printf("%s %s %d \n", p[i].nume, p[i].prenume, p[i].scor);
			ok = 0;
		}

	if (ok == 1)
		printf("Nu exista participanti care au numele ce incepe cu litera respectiva. \n");

	return ok;
}

int sorteazaCrescatorNume()
{
	/*
		Sorteaza crescator dupa nume sirul de participanti.
		Input: -
		Output: 0, daca sirul nu era ordonat inainte
				1, daca sirul era deja ordonat
	*/

	int i, j, ok = 1;
	for (i = 1; i < len; i++)
		for (j = i + 1; j <= len; j++)
			if (strcmp(p[i].nume, p[j].nume) > 0)
			{
				Participant aux = p[i];
				p[i] = p[j];
				p[j] = aux;
				ok = 0;
			}
	return ok;
}

int sorteazaDescrescatorNume()
{
	/*
		Sorteaza descrescator dupa nume sirul de participanti.
		Input: - 
		Output: 0, daca sirul nu era ordonat inainte
				1, daca sirul era deja ordonat
	*/

	int i, j, ok = 1;
	for (i = 1; i < len; i++)
		for (j = i + 1; j <= len; j++)
			if (strcmp(p[i].nume, p[j].nume) < 0)
			{
				Participant aux = p[i];
				p[i] = p[j];
				p[j] = aux;
				ok = 0;
			}
	return ok;
}

int sorteazaCrescatorScor()
{
	/*
		Sorteaza crescator dupa scor sirul de participanti.
		Input: -
		Output: 0, daca sirul nu era ordonat inainte
				1, daca sirul era deja ordonat
	*/

	int i, j, ok = 1;
	for (i = 1; i < len; i++)
		for (j = i + 1; j <= len; j++)
			if (p[i].scor > p[j].scor)
			{
				Participant aux = p[i];
				p[i] = p[j];
				p[j] = aux;
				ok = 0;
			}
	return ok;
}

int sorteazaDescrescatorScor()
{
	/*
		Sorteaza descrescator dupa scor sirul de participanti.
		Input: -
		Output: 0, daca sirul nu era ordonat inainte
				1, daca sirul era deja ordonat
	*/

	int i, j, ok = 1;
	for (i = 1; i < len; i++)
		for (j = i + 1; j <= len; j++)
			if (p[i].scor < p[j].scor)
			{
				Participant aux = p[i];
				p[i] = p[j];
				p[j] = aux;
				ok = 0;
			}
	return ok;
}