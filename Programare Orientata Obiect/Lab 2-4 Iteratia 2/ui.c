#include "ui.h"
#include "service.h"
#include <stdio.h>
#include <string.h>

void meniuPrincipal()
{
	printf("1 - Adaugare participant nou. \n");
	printf("2 - Actualizare participant existent. \n");
	printf("3 - Stergere participant. \n");
	printf("4 - Afisarea participantilor filtrati dupa o proprietate. \n");
	printf("5 - Sortarea participantilor dupa: nume sau scor. \n");
	printf("6 - Afiseaza participantii. \n");
	printf("0 - Exit. \n");
	printf("\n");
}

void meniuFiltrare()
{
	printf("1 - Filtrare participanti care au scor mai mic decat o valoare data. \n");
	printf("2 - Filtrare participanti care au numele care incepe cu o litera data. \n");
}

void meniuSortare()
{
	printf("1 - Sortare dupa nume. \n");
	printf("2 - Sortare dupa scor. \n");
}

void meniuMonotonie()
{
	printf("1 - Crescator. \n");
	printf("2 - Descrescator. \n");
}

void run(Ui* u)
{
	meniuPrincipal();

	while (1)
	{
		int cmd = 0;
		printf("Introduceti o comanda: ");
		scanf_s("%d", &cmd);

		switch (cmd)
		{
		case 0:
		{
			return;
		}

		case 1:
		{

			char num[20], prenum[20];
			int s;

			printf("Introduceti numele: ");
			scanf_s("%s", &num, 16);

			printf("Introduceti prenumele: ");
			scanf_s("%s", &prenum, 16);

			printf("Introduceti scorul: ");
			scanf_s("%d", &s);

			int cod = adaugareParticipant(u->s, num, prenum, s);
			if (cod == 1)
				printf("Nume invalid. \n");
			if (cod == 2)
				printf("Prenume invalid. \n");
			if (cod == 3)
				printf("Scor invalid. \n");
			if (cod == 4)
				printf("Participantul deja exista. \n");

			break;
		}

		case 2:
		{
			char num[20], prenum[20];
			int s;

			printf("Introduceti numele: ");
			scanf_s("%s", &num, 16);

			printf("Introduceti prenumele: ");
			scanf_s("%s", &prenum, 16);

			printf("Introduceti scorul: ");
			scanf_s("%d", &s);

			int cod = actualizareParticipant(u->s, num, prenum, s);
			if (cod == 1)
				printf("Nume invalid. \n");
			if (cod == 2)
				printf("Prenume invalid. \n");
			if (cod == 3)
				printf("Scor invalid. \n");
			if (cod == 4)
				printf("Participantul pe care vreti sa il actualizati nu exista. \n");

			break;
		}

		case 3:
		{
			char num[20], prenum[20];

			printf("Introduceti numele: ");
			scanf_s("%s", &num, 16);

			printf("Introduceti prenumele: ");
			scanf_s("%s", &prenum, 16);

			int cod = stergereParticipant(u->s, num, prenum);
			if (cod == 1)
				printf("Nume invalid. \n");
			if (cod == 2)
				printf("Prenume invalid. \n");
			if (cod == 3)
				printf("Scor invalid. \n");
			if (cod == 4)
				printf("Participantul pe care vreti sa il stergeti nu exista. \n");
			if(cod == 0)
				printf("Stergerea s-a efectuat cu succes. Apasa tasta 6 pentru a vedea lista curenta. \n");

			break;
		}

		case 4:
		{
			int criteriu = 0;
			meniuFiltrare();
			printf("Introduceti criteriul de filtrare: ");
			scanf_s("%d", &criteriu);

			if (criteriu == 1)
			{
				int valoare = 0;
				printf("Introduceti valoarea: ");
				scanf_s("%d", &valoare);

				int ok = filtrareValoare(u->s, valoare);

				if (ok == 1)
					printf("Nu exista participanti cu scor mai mic decat valoarea data. \n");
			}
			else
				if (criteriu == 2)
				{
					char litera[2] = "A";
					printf("Introduceti litera: ");
					scanf_s("%s", &litera, 2);

					int ok = filtrareLitera(u->s, litera);
					if (ok == 1)
						printf("Nu exista participant cu numele care incepe cu litera data. \n");
				}
				else
					printf("Criteriu invalid. \n");

			break;
		}
		
		case 5:
		{
			meniuSortare();
			int criteriu = 0;
			printf("Introduceti criteriul: ");
			scanf_s("%d", &criteriu);

			meniuMonotonie();
			int mon = 0;
			printf("Introduceti monotonia: ");
			scanf_s("%d", &mon);

			if (criteriu == 1)
				if (mon == 1)
					sortareCrescatorNume(u->s);
				else
					if (mon == 2)
						sortareDescrescatorNume(u->s);
					else
						printf("Criteriu pentru monotonie invalid. \n");
			else
				if (criteriu == 2)
					if (mon == 1)
						sortareCrescatorScor(u->s);
					else
						if (mon == 2)
							sortareDescrescatorScor(u->s);
						else
							printf("Criteriu pentru monotonie invalid. \n");
				else
					printf("Criteriu de sortare invalid. \n"); 
			afisareParticipanti(u->s);
			break;
		}
		case 6:
		{
			int ok = afisareParticipanti(u->s);
			if (ok == 1)
			{
				printf("Nu exista participanti. \n");
			}
			break;
		}

		default:
		{
			printf("Comanda invalida. \n");

			break;
		}
		}
	}
}