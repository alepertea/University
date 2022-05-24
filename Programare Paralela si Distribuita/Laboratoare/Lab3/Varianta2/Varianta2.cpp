#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "mpi.h"

using namespace std;
using namespace std::chrono;

void writeNumber(string filename, int number[], int N)
{
	ofstream file(filename);

	if (!file)
	{
		throw new exception("Problem in opening the file for writing!");
	}

	for (int i = N - 1; i >= 0; i--)
		file << number[i];

	file.close();
}

void insert(int number[], int n, int element)
{
	for (int i = n; i > 0; i--)
		number[i] = number[i - 1];
	number[0] = element;
}

int main(int argc, char** argv)
{
	int rc = MPI_Init(NULL, NULL);
	if (rc != MPI_SUCCESS)
	{
		cout << "Error initializing MPI!";
		MPI_Abort(MPI_COMM_WORLD, rc);
	}

	int p, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;

	const int N1 = 100, N2 = 100000;
	int N = max(N1, N2);
	int n = N;
	while (n % p != 0)
		n++;

	int* number1 = new int[n]; 
	int* number2 = new int[n];
	int* result = new int[n + 1];

	auto startTime = chrono::high_resolution_clock::now();

	if (rank == 0)
	{
		ifstream file_Numar1("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab3\\Varianta2\\Varianta2\\Varianta2\\Numar1.txt");
		ifstream file_Numar2("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab3\\Varianta2\\Varianta2\\Varianta2\\Numar2.txt");

		int digit;
		for (int i = 0; i < N1; i++)
		{
			file_Numar1 >> digit;
			insert(number1, n, digit);
		}
		if (N1 < n)
		{
			for (int i = N1; i < n; i++)
				number1[i] = 0;
		}
		for (int i = 0; i < N2; i++)
		{
			file_Numar2 >> digit;
			insert(number2, n, digit);
		}
		if (N2 < n)
		{
			for (int i = N2; i < n; i++)
				number2[i] = 0;
		}
	}
	
	int* number1_local = new int[n / p];
	int* number2_local = new int[n / p];
	int* result_local = new int[n / p];

	MPI_Scatter(number1, n / p, MPI_INT, number1_local, n / p, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(number2, n / p, MPI_INT, number2_local, n / p, MPI_INT, 0, MPI_COMM_WORLD);

	int carry = 0;
	for (int i = 0; i < n / p; i++)
	{
		int res = number1_local[i] + number2_local[i] + carry;
		result_local[i] = res % 10;
		carry = res / 10;
	}

	if (rank < p - 1)
		MPI_Send(&carry, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
	else
		MPI_Send(&carry, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

	if (rank > 0)
		MPI_Recv(&carry, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
	else
		MPI_Recv(&carry, 1, MPI_INT, p - 1, 0, MPI_COMM_WORLD, &status);

	if (rank > 0)
	{
		int i = 0;
		while (carry == 1 && i < n / p)
		{
			int carryRes = result_local[i] + carry;
			carryRes /= 10;
			result_local[i] = carryRes % 10;
			i++;
		}
	}

	MPI_Gather(result_local, n / p, MPI_INT, result, n / p, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		if (carry != 0)
		{
			result[N] = carry;
			N++;
		}

		writeNumber("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab3\\Varianta2\\Varianta2\\Varianta2\\Numar3.txt", result, n);

		auto endTime = chrono::high_resolution_clock::now();

		cout << chrono::duration<double, milli>(endTime - startTime).count() << endl;
	}

	MPI_Finalize();

	return 0;
}