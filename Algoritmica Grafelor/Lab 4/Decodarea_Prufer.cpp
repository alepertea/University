#include<fstream>
#include<iostream>
#include<vector>

using namespace std;

struct Nod
{
    int parinte;
    int numarFii;
};

int n;
vector<Nod> noduri;
vector<int> prufer;

void DecodareaPrufer()
{
    for (int i = 0; i < n; i++)
    {
        bool ok = false;
        for (int j = 0; j <= n && ok == false; j++)
        {
            if (noduri[j].numarFii == 1)
            {
                noduri[j].parinte = prufer[i];
                noduri[prufer[i]].numarFii--;
                noduri[j].numarFii--;
                ok = true;
            }
        }
    }

    int nod1 = -1;
    int nod2 = -1;
    for (int i = 0; i <= n; i++)
    {
        if (noduri[i].numarFii == 1)
        {
            if (nod1 == -1)
            {
                nod1 = i;
            }
            else
            {
                nod2 = i;
            }
        }
    }
    noduri[nod2].parinte = nod1;
    noduri[nod1].parinte = -1;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Trebuie sa introduceti fisierele de intrare si iesire! \n";
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    fin >> n;

    noduri.resize(n + 3);
    for (int i = 0; i <= n; i++)
    {
        noduri[i].parinte = 0;
        noduri[i].numarFii = 1;
    }

    int x = 0;
    for (int i = 0; i < n; i++)
    {
        fin >> x;
        prufer.push_back(x);
        noduri[x].numarFii += 1;
    }

    DecodareaPrufer();

    fout << n + 1 << '\n';
    for (int i = 0; i <= n; i++)
    {
        fout << noduri[i].parinte << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
