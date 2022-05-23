#include <stdio.h>
#include <string.h>
#include "service.h"
#include "domain.h"

void meniuPrincipal()
{
	printf("1 - Adaugare participant nou. \n");
	printf("2 - Actualizare participant existent. \n");
	printf("3 - Stergere participant. \n");
	printf("4 - Afisarea participantilor filtrati dupa o proprietate. \n");
	printf("5 - Sortarea participantilor dupa: nume sau scor. \n");
	printf("6 - Afisare participanti existenti. \n");
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

void input()
{
	char num[20], prenum[20];
	int s;

	printf("Introduceti numele: ");
	scanf_s("%s", &num, 16);

	printf("Introduceti prenumele: ");
	scanf_s("%s", &prenum, 16);

	printf("Introduceti scorul: ");
	scanf_s("%d", &s);
}

int run()
{
	meniuPrincipal();
	initializare();

	while (1)
	{
		int cmd = 0;
		printf("Introduceti o comanda: ");
		scanf_s("%d", &cmd);

		switch (cmd)
		{
			case 0:
			{
				return 0;
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

				adaugareParticipant(num, prenum, s);

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

				actualizareParticipant(num, prenum, s);

				break;
			}

			case 3:
			{
				char num[20], prenum[20];
				int s = 0;

				printf("Introduceti numele: ");
				scanf_s("%s", &num, 16);

				printf("Introduceti prenumele: ");
				scanf_s("%s", &prenum, 16);

				stergereParticipant(num, prenum);

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

					filtrareValoare(valoare);
				}
				else
					if (criteriu == 2)
					{
						char litera[] = "A";
						printf("Introduceti litera: ");
						scanf_s("%s", &litera, 16);
						filtrareLitera(litera);
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
						sortareCrescatorNume();
					else
						if (mon == 2)
							sortareDescrescatorNume();
						else
							printf("Criteriu pentru monotonie invalid. \n");
				else
					if (criteriu == 2)
						if (mon == 1)
							sortareCrescatorScor();
						else
							if (mon == 2)
								sortareDescrescatorScor();
							else
								printf("Criteriu pentru monotonie invalid. \n");
					else
						printf("Criteriu de sortare invalid. \n");

				break;
			}

			case 6:
			{
				afisareParticipanti();

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