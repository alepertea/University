#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

vector<int> culoare;
vector<vector<int>> adj;
stack<int> stiva;
int n, m;

ifstream fin("input.txt");
ofstream fout("output.txt");

bool valid(int nod, int c)
{
	for (int i = 0; i < n; i++)
		if (adj[nod][i] == 1 && c == culoare[i])
			return false;
	return true;
}

int nrCulori(vector<int> culoare)
{
	int max = 0;
	for (unsigned int i = 0; i < culoare.size(); i++)
	{
		if (culoare[i] > max)
			max = culoare[i];
	}
	return max + 1;
}

void printSolution(vector<int> culoare)
{
	fout << nrCulori(culoare) << '\n';
	for (unsigned int i = 0; i < culoare.size(); i++)
	{
		fout << culoare[i] << " ";
	}
}

void colorare(int nod)
{
	stiva.push(nod);
	while (stiva.empty() == false)
	{
		int nodCurent = stiva.top();
		stiva.pop();

		for (int c = 0; c < n && culoare[nodCurent] == -1; c++)
			if (valid(nodCurent, c) == true)
				culoare[nodCurent] = c;

		for(int i = 0; i < n; i++)
			if (adj[nodCurent][i] == 1 && culoare[i] == -1)
				stiva.push(i);
	}
}

int main()
{
	fin >> n >> m;

	culoare.resize(n, -1);

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
	}

	colorare(0);
	
	printSolution(culoare);
	return 0;
}