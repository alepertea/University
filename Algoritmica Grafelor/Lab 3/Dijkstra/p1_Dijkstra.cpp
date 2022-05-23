#include <iostream>
#include <fstream>
#include <queue>
#include <string>

constexpr auto INF = 99999;

using namespace std;

struct pondere
{
	int nod_sursa;
	int nod_destinatie;
	int cost;			// costul dintre nod1 -> nod2
};

int n;				// numarul de noduri
int m;				// numarul de muchii
int nodSursa;		// nodul sursa
int D[100];			// vectorul de drumuri minime de la nodul sursa la nodul index
pondere p[100];		// vector de ponderi
int coada[100];		// vector ca sa verific daca un nod se afla in coada sau nu

string fisier_intrare = "";
string fisier_iesire = "";

queue <int> Q;

void Initializare()
{
	cout << "Introduceti fisierul de intrare: ";
	cin >> fisier_intrare;

	cout << "Introduceti fisierul de iesire: ";
	cin >> fisier_iesire;

	ifstream fin(fisier_intrare);

	fin >> n >> m >> nodSursa;

	int x, y, w;
	for (int i = 1; i <= m; i++)
	{
		fin >> x >> y >> w;
		p[i].nod_sursa = x;
		p[i].nod_destinatie = y;
		p[i].cost = w;
	}

	fin.close();
}

void Dijkstra(int nodSursa)
{
	for (int i = 0; i < n; i++)
	{
		if (i == nodSursa)
			D[i] = 0;
		else
			D[i] = INF;
	}

	Q.push(nodSursa);
	coada[nodSursa] = 1;

	while (!Q.empty())
	{
		int nodCurent = Q.front();
		Q.pop();
		coada[nodCurent] = 0;
		for (int i = 1; i <= m; i++)
		{
			if (p[i].nod_sursa == nodCurent)
			{
				if (D[nodCurent] + p[i].cost < D[p[i].nod_destinatie])
				{
					D[p[i].nod_destinatie] = D[nodCurent] + p[i].cost;
					if (coada[p[i].nod_destinatie] == 0)
					{
						coada[p[i].nod_destinatie] = 1;
						Q.push(p[i].nod_destinatie);
					}
				}
			}
		}
	}
}

void Afisare()
{
	ofstream fout(fisier_iesire);

	for (int i = 0; i < n; i++)
		if (D[i] != INF)
			fout << D[i] << " ";
		else
			fout << "INF" << " ";

	cout << endl;
	cout << "Deschideti fisierul " << fisier_iesire << " pentru rezultat." << endl;

	fout.close();
}

int main()
{
	Initializare();
	Dijkstra(nodSursa);
	Afisare();

	return 0;
}