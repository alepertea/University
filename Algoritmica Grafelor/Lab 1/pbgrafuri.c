#include <stdio.h>

#define INF 9999

typedef struct
{
	int v1, v2;
}Muchie;

Muchie sirMuchii[100];
int vf1, vf2;

int adiacenta[100][100];
int incidenta[100][100];
int distante[100][100];

void citireNumere(int *n, int *m)
{
	printf("Dati numarul de noduri: ");
	scanf_s("%d", n);

	printf("Dati numarul de muchii: ");
	scanf_s("%d", m);
}

void citireMuchii(int m)
{
	int i;
	for (i = 1; i <= m; i++)
	{
		scanf_s("%d%d", &vf1, &vf2);
		adiacenta[vf1][vf2] = adiacenta[vf2][vf1] = 1;
	}
}

int main(int arcg, char** argv)
{
	int n = 0;
	int m = 0;

	citireNumere(&n, &m);
	citireMuchii(m);

	int i;

	printf("Matricea de adiacenta:\n");
	int j;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			printf("%d ", adiacenta[i][j]);
		}
		printf("\n");
	}

	//Matricea de incidenta
	int c = 1;
	for (i = 1; i <= n; i++)
	{
		for (j = i + 1; j <= n; j++)
		{
			if (adiacenta[i][j] == 1)
			{
				incidenta[i][c] = 1;
				incidenta[j][c] = 1;
				sirMuchii[c].v1 = i;
				sirMuchii[c].v2 = j;
				c++;  
			}
		}
	}

	printf("Matricea de incidenta:\n");
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= m; j++)
		{
			printf("%d ", incidenta[i][j]);
		}
		printf("\n");
	}

	printf("Lista de muchii:\n");
	for (i = 1; i < c; i++)
	{
		printf("%d %d \n", sirMuchii[i].v1, sirMuchii[i].v2);
	}

	//Graf regulat
	int suma = 0;
	int ok = 1;
	for (i = 1; i <= n; i++)
	{
		suma = suma + adiacenta[1][i];
	}
	for (i = 2; i <= n; i++)
	{
		int s = 0;
		for (j = 1; j <= n && ok == 1; j++)
		{
			s = s + adiacenta[i][j];
		}
		if (suma != s)
		{
			ok = 0;
		}
	}
	if (ok == 1)
	{
		printf("Graful este regulat.\n");
	}
	else
	{
		printf("Graful nu este regulat.\n");
	}


	//Noduri izolate
	int okIzo = 0;
	for (i = 1; i <= n; i++)
	{
		int s = 0;
		for (j = 1; j <= n; j++)
		{
			s = s + adiacenta[i][j];
		}
		if (s == 0)
		{
			okIzo = 1;
			printf("Nodul %d este izolat.\n", i);
		}
	}
	if (okIzo == 0)
	{
		printf("Nu exista noduri izolate in graf.\n");
	}

	//Matricea distantelor
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (i == j)
				distante[i][j] = 0;
			else
				distante[i][j] = INF;
		}
	}
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (adiacenta[i][j] == 1)
				distante[i][j] = 1;
		}
	}
	int k;
	for (k = 1; k <= n; k++)
	{
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
			{
				if (distante[i][k] + distante[k][j] < distante[i][j] && distante[i][k] != INF && distante[k][j] != INF)
					distante[i][j] = distante[i][k] + distante[k][j];
			}
		}
	}
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (distante[i][j] == INF)
				printf("-1 ");
			else
				printf("%d ", distante[i][j]);
		}
		printf("\n");
	}
}