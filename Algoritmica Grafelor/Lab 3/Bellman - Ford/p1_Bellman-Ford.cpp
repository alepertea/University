#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
vector<int> D;			// vectorul de drumuri minime de la nodul sursa la nodul index
vector<pondere> p;		// vector de ponderi

string fisier_intrare = "";
string fisier_iesire = "";

void Initializare()
{
    cout << "Introduceti fisierul de intrare: ";
    cin >> fisier_intrare;

    cout << "Introduceti fisierul de iesire: ";
    cin >> fisier_iesire;
    
    ifstream fin(fisier_intrare);

    fin >> n >> m >> nodSursa;

    D.resize(n);
    p.resize(m);

    int x, y, w;
    for (int i = 0; i < m; i++)
    {
        fin >> x >> y >> w;
        p[i].nod_sursa = x;
        p[i].nod_destinatie = y;
        p[i].cost = w;
    }

    fin.close();
}

void Relax(int sursa, int destinatie, int cost)
{
    if (D[sursa] != INF && D[sursa] + cost < D[destinatie])
        D[destinatie] = D[sursa] + cost;
}

bool Bellman_Ford(int nodSursa)
{
    for (int i = 0; i < n; i++)
    {
        if (i == nodSursa)
            D[i] = 0;
        else
            D[i] = INF;
    }

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < m; j++)
            Relax(p[j].nod_sursa, p[j].nod_destinatie, p[j].cost);

    for (int i = 0; i < m; i++)
        if (D[p[i].nod_sursa] != INF && D[p[i].nod_sursa] + p[i].cost < D[p[i].nod_destinatie])
            return false;
    return true;
}

void Afisare(bool ok)
{
    ofstream fout(fisier_iesire);

    if (ok == false)
    {
        fout << "Circuit de pondere negativa!";
    }
    else
    {
        for (int i = 0; i < n; i++)
            if (D[i] != INF)
                fout << D[i] << " ";
            else
                fout << "INF" << " ";
    }

    cout << endl;
    cout << "Deschideti fisierul " << fisier_iesire << " pentru rezultat." << endl;

    fout.close();
}

int main()
{
    Initializare();
    bool ok = Bellman_Ford(nodSursa);
    Afisare(ok);

    return 0;
}