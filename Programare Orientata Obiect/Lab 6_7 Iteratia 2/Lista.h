#include <iostream>
#include <map>
#include <vector>

using namespace std;


// returneaza numarul elementelor care nu sunt unice in vector
// arunca exceptie daca vectorul este gol
int f(vector<int> l)
{
	if (l.size() < 1)
		throw exception("Illegal argument");
	map<int, int> m;
	for (auto e : l)
		m[e]++;
	int rez{ 0 };
	for (auto e : m)
		if (e.second > 1)
			rez++;
	return rez;
}

void test()
{
	vector<int> t;
	int rez;
	try
	{
		rez = f(t);
		assert(false);
	}
	catch (exception&)
	{
		assert(true);
	}
	t.push_back(1);
	t.push_back(2);
	t.push_back(3);
	t.push_back(2);
	t.push_back(1);
	t.push_back(4);
	t.push_back(5);
	assert(f(t) == 2);
}

int main()
{
	test();
	return 0;
}