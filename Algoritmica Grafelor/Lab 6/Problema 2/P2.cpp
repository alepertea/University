#include <fstream>
#include <vector>
#include <queue>
#include <iostream>

constexpr auto INF = 9999999;;

using namespace std;

vector<vector<int>> capacitate;
vector<vector<int>> fluxuri;
vector<bool> vizitat;
vector<int> tati;
vector<int> nrStudenti;
queue<int> Q;
int n, s, d, m;

ifstream fin("input.txt");
ofstream fout("output.txt");

int BFS(int nodSursa, int nodDestinatie)
{
	for (int i = 0; i < n; i++)
	{
		tati[i] = -1;
		vizitat[i] = false;
	}

	Q.push(nodSursa);
	vizitat[nodSursa] = true;
	while (Q.empty() == false)
	{
		int nodCurent = Q.front();
		Q.pop();

		for (int i = nodSursa; i <= nodDestinatie; i++)
			if (vizitat[i] == false)
				if (capacitate[nodCurent][i] > fluxuri[nodCurent][i])
				{
					Q.push(i);
					tati[i] = nodCurent;
					vizitat[i] = true;
				}
	}

	if (tati[nodDestinatie] != -1)
		return 1;
	return 0;
}

int EdmondsKarp(int nodSursa, int nodDestinatie)
{
	int fluxMaxim = 0;
	while (true)
	{
		int flux = BFS(nodSursa, nodDestinatie);
		if (flux == 0)
			break;

		int minim = INF;
		int nodCurent = nodDestinatie;
		while(nodCurent != nodSursa)
		{
			int nodPrecedent = tati[nodCurent];
			if (capacitate[nodPrecedent][nodCurent] - fluxuri[nodPrecedent][nodCurent] < minim)
				minim = capacitate[nodPrecedent][nodCurent] - fluxuri[nodPrecedent][nodCurent];
			nodCurent = nodPrecedent;
		}

		fluxMaxim += minim;

		nodCurent = nodDestinatie;
		while (nodCurent != nodSursa)
		{
			int nodPrecedent = tati[nodCurent];
			fluxuri[nodPrecedent][nodCurent] += minim;
			fluxuri[nodCurent][nodPrecedent] -= minim;
			nodCurent = nodPrecedent;
		}
	}

	return fluxMaxim;
}

void printSolution()
{
	int flux = EdmondsKarp(s, d);

	fout << flux << '\n';

	fout.close();
}

void citire()
{
	fin >> n >> m >> s >> d;

	capacitate.resize(n);
	fluxuri.resize(n);
	tati.resize(n, -1);
	vizitat.resize(n, false);

	for (int i = 0; i < n; i++)
	{
		capacitate[i].resize(n, 0);
		fluxuri[i].resize(n, 0);
	}

	int x, y, cap;
	for (int i = 0; i < m; i++)
	{
		fin >> x >> y >> cap;
		capacitate[x][y] = cap;
	}

	fin.close();
}

int main()
{
	citire();
	printSolution();
	return 0;
}