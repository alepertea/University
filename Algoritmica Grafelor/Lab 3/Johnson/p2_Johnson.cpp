#include <iostream>
#include <string>
#include <fstream>
#include <queue>
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
int D[100];			// vectorul de drumuri minime de la nodul sursa la nodul index
int coada[100];		// vector ca sa verific daca un nod se afla in coada sau nu
pondere p[100];		// vector de ponderi
int muchie[100];

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

    fin >> n >> m;

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

    for (int i = 0; i < n; i++)
        for (int j = 1; j <= m + n; j++)
            Relax(p[j].nod_sursa, p[j].nod_destinatie, p[j].cost);

    for (int i = 1; i <= m + n; i++)
        if (D[p[i].nod_sursa] != INF && D[p[i].nod_sursa] + p[i].cost < D[p[i].nod_destinatie])
            return false;
    return true;
}

void Afisare(bool ok)
{
    ofstream fout(fisier_iesire);
    if (ok == false)
        fout << -1;

}

void sortMuchii()
{
    for (int i = 1; i < m; i++)
    {
        for (int j = i + 1; j <= m; j++)
        {
            if (p[i].nod_sursa > p[j].nod_sursa)
            {
                pondere aux = p[i];
                p[i] = p[j];
                p[j] = aux;
            }
            else
            {
                if (p[i].nod_sursa == p[j].nod_sursa)
                {
                    if (p[i].nod_destinatie > p[j].nod_destinatie)
                    {
                        pondere aux = p[i];
                        p[i] = p[j];
                        p[j] = aux;
                    }
                }
            }
        }
    }
}

int Johnson()
{
    for (int i = 0; i < n; i++)
    {
        p[m + i + 1].nod_sursa = n;
        p[m + i + 1].nod_destinatie = i;
        p[m + i + 1].cost = 0;
    }

    bool ok = Bellman_Ford(n);

    if (ok == false)
    {
        Afisare(ok);
        return -1;
    }

    sortMuchii();

    for (int i = 1; i <= m; i++)
        muchie[i] = p[i].cost + D[p[i].nod_sursa] - D[p[i].nod_destinatie];
    return 0;
}

int main()
{
    Initializare();
    int john = Johnson();

    if (john == 0)
    {
        ofstream fout(fisier_iesire);
        for (int i = 1; i <= m; i++)
            fout << p[i].nod_sursa << " " << p[i].nod_destinatie << " " << muchie[i] << endl;


        for (int i = 0; i < n; i++)
        {
            Dijkstra(i);
            for (int i = 0; i < n; i++)
                if (D[i] != INF)
                    fout << D[i] << " ";
                else
                    fout << "INF" << " ";
            fout << '\n';
        }
        fout.close();
    }


    cout << endl;
    cout << "Deschideti fisierul " << fisier_iesire << " pentru rezultat." << endl;

    return 0;
}