#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

struct Nod
{
    int parinte;
    int numarFii;
    int vizitat;
};

int n;                  // numarul de noduri
vector<Nod> noduri;     // vector de noduri
vector<int> prufer;     // vector in care se afla nodurile codificate

void CodareaPrufer()
{
    for (int i = 0; i < n - 1; i++)
    {
        int minim = n + 1;
        for (int j = 0; j < n; j++)
        {
            if (noduri[j].numarFii == 0 && minim > j&& noduri[j].vizitat == 0)
            {
                minim = j;
            }
        }
        prufer.push_back(noduri[minim].parinte);
        noduri[minim].vizitat = 1;
        noduri[noduri[minim].parinte].numarFii--;
    }
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

    noduri.resize(n);
    for (int i = 0; i < n; i++)
    {
        noduri[i].parinte = 0;
        noduri[i].numarFii = 0;
        noduri[i].vizitat = 0;
    }

    int x = 0;
    for (int i = 0; i < n; i++)
    {
        fin >> x;
        if (x != -1)
        {
            noduri[i].parinte = x;
            noduri[x].numarFii += 1;
        }
    }

    CodareaPrufer();

    int m = prufer.size();
    fout << m << '\n';
    for (int i = 0; i < m; i++)
    {
        fout << prufer[i] << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
