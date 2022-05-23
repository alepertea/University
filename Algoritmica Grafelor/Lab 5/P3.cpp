#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<vector<int>> adj;	// matricea de adiacenta
vector<int> nrVecini;		// vector pentru numarul de vecini al fiecarui nod
vector<int> euler;			// vector cu nodurile din ciclul eulerian

int n, m;					// numarul de noduri si numarul de muchii

void CicluEulerian(int nod)
{
	while (nrVecini[nod] != 0)
	{
		int nodAdiacent = 0;
		bool gasit = false;
		for (int i = 0; i < n; i++)
		{
			if (adj[nod][i] == 1 && gasit == false)
			{
				nodAdiacent = i;
				gasit = true;
			}
		}

		adj[nod][nodAdiacent] = 0;
		adj[nodAdiacent][nod] = 0;
		nrVecini[nod]--;
		nrVecini[nodAdiacent]--;

		CicluEulerian(nodAdiacent);
	}
	euler.push_back(nod);
}

int main(int argc, char* argv[])
{
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);

	fin >> n >> m;
	nrVecini.resize(n, 0);
	adj.resize(n);

	for (int i = 0; i < n; i++)
	{
		adj[i].resize(n, 0);
	}

	int x, y;
	for (int i = 0; i < m; i++)
	{
		fin >> x >> y;
		adj[x][y] = 1;
		adj[y][x] = 1;
		nrVecini[x]++;
		nrVecini[y]++;
	}

	CicluEulerian(0);

	for (unsigned int i = 0; i < euler.size() - 1; i++)
	{
		fout << euler[i] << " ";
	}

	fin.close();
	fout.close();

	return 0;
}