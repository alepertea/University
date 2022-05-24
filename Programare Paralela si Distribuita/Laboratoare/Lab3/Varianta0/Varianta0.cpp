#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

void writeNumber(string filename, vector<int> number)
{
	ofstream file(filename);

	if (!file)
	{
		throw new exception("Problem in opening the file for writing!");
	}

	for (auto it = number.rbegin(); it != number.rend(); it++)
		file << *it;

	file.close();
}

void readNumber(string filename, vector<int>& number, int& n)
{
	ifstream file(filename);

	if (!file)
	{
		throw new exception("Problem in opening the file for reading!");
	}

	file >> n;
	int digit;
	for (int i = 0; i < n; i++)
	{
		file >> digit;
		number.insert(number.begin(), digit);
	}

	file.close();
}

void initializeVectors(vector<int>& number1, vector<int>& number2, int& n)
{
	int n1, n2;
	readNumber("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab3\\Varianta0\\Varianta0\\Varianta0\\Numar1.txt", number1, n1);
	readNumber("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab3\\Varianta0\\Varianta0\\Varianta0\\Numar2.txt", number2, n2);

	if (n1 > n2)
	{
		n = n1;
		number2.resize(n);
	}
	else
	{
		n = n2;
		number2.resize(n);
	}
}

void add(vector<int> number1, vector<int> number2, vector<int>& result, int n)
{
	int carry = 0;
	for (int i = 0; i < n; i++)
	{
		int res = number1[i] + number2[i] + carry;
		result[i] = res % 10;
		carry = res / 10;
	}
	if (carry == 1)
		result.push_back(1);
}

int main(int argc, char** argv)
{
	int n;
	vector<int> number1, number2, result;
	
	auto startTime = high_resolution_clock::now();

	initializeVectors(number1, number2, n);
	result.resize(n + 1);

	add(number1, number2, result, n);

	writeNumber("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab3\\Varianta0\\Varianta0\\Varianta0\\Numar3.txt", result);

	auto endTime = high_resolution_clock::now();

	cout << duration<double, milli>(endTime - startTime).count() << endl;

	return 0;
}