#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

// Nu s-au specificat modurile de citire si de afisare asa ca am ales sa lucrez cu fisiere
ifstream fin("graf.in");
ofstream fout("graf.out");

int n, m;           // numar de noduri, numar de muchii
int G[101][101];    // matrice de adiacenta
int vizitat[101];

void reinitializare()
{
    /*
        Marcam toate nodurile ca fiind nevizitate.
    */
    for (int i = 1; i <= n; i++)
        vizitat[i] = 0;
}

void DFS(int nodCurent)
{
    vizitat[nodCurent] = 1;
    for (int i = 1; i <= n; i++)
        if (G[nodCurent][i] == 1 && vizitat[i] == 0)
            DFS(i);
}

void afisare()
{
    /*
        Afisam vectorul de vizitati, astfel din nodul apelat in DFS putem ajunge in nodurile marcate cu 1
        Cele care raman 0 sunt inaccesibile din nodul sursa de pornire
    */
    for (int i = 1; i <= n; i++)
        fout << vizitat[i] << ' ';
    fout << '\n';
}


int main()
{
    fin >> n >> m;

    int a, b;

    for (int i = 1; i <= m; i++)
    {
        fin >> a >> b;
        G[a][b] = 1;
    }

    reinitializare();

    for (int i = 1; i <= n; i++)
    {
        DFS(i);
        afisare();
        reinitializare();       // reinializam vectorul ca sa il putem folosi iar si la urmatorul nod
    }

    fin.close();
    fout.close();

    cout << "Deschideti fisierul graf.out pentru rezultat. \n";

    return 0;
}