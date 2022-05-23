#include <iostream>
#include <fstream>
#include <queue>
#define INF 99999

using namespace std;

ifstream fin("graf.txt");

int n, m, nodSursa;         // numar de noduri, numar de muchii, nod sursa
int l[101];                 // lungimea drumului de la nodul sursa la fiecare nod
int G[101][101];            // matrice de adiacenta
int p[101];                 // vectori de parinti

void afiseaza(int nod, int lungime)
{
    if (nod == nodSursa)    // cazul particular de oprire, cand parcurgerea ajunge la nodul sursa
        cout << "Lungime: " << lungime + 1 << '\n' << "Noduri: " << nod << " ";
    else
    {
        afiseaza(p[nod], lungime + 1);
        cout << nod << " ";
    }
}

int main()
{
    fin >> n;

    cout << "Introduceti nodul sursa: ";
    cin >> nodSursa;

    int a, b;

    while (fin >> a >> b)
        G[a][b] = 1;

    for (int i = 1; i <= n; i++)
    {
        l[i] = INF;
        p[i] = -1;       // punem initial ca toate nodurile sa aiba parintele -1 ca sa putem diferentia la final nodurile izolate
    }

    l[nodSursa] = 0;
    p[nodSursa] = -1;

    queue <int> Q;

    Q.push(nodSursa);

    while (!Q.empty())
    {
        int nodCurent = Q.front();
        for (int j = 1; j <= n; j++)    // parcurgem nodurile grafului
            if (G[nodCurent][j] == 1)   // parcurgem vecinii nodului curent
                if (l[j] == INF)
                {
                    p[j] = nodCurent;
                    l[j] = l[nodCurent] + 1;
                    Q.push(j);
                }
        Q.pop();
    }

    for (int i = 1; i <= n; i++)            // parcurgem nodurile
        if (i != nodSursa && p[i] != -1)    // p[i] != -1 => nodul i nu este izolat
        {
            cout << '\n';
            cout << "De la nodul " << nodSursa << " la nodul " << i << '\n';
            afiseaza(i, 0);
            cout << '\n';
        }
        else
            if (i == nodSursa)
            {
                cout << '\n';
                cout << "De la nodul " << i << " la el insusi" << '\n';
                cout << "Lungime: 1" << '\n' << "Nod: " << nodSursa << '\n';
            }

    fin.close();

    return 0;
}