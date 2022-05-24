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

	for (int i = N - 1; i >= 0; i--) {
		file << number[i];
	}

	file.close();
}

void insert(int number[], int n, int element)
{
	for (int i = n; i > 0; i--)
	{
		number[i] = number[i - 1];
	}
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
	const int N = max(N1, N2) + 1;
	int number1[N - 1], number2[N - 1], result[N];
	int n = N;

	int start, end;

	if (rank == 0)
	{
		ifstream file_Numar1("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab3\\Varianta1\\Varianta1\\Varianta1\\Numar1.txt");
		ifstream file_Numar2("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab3\\Varianta1\\Varianta1\\Varianta1\\Numar2.txt");

		auto startTime = high_resolution_clock::now();

		int chunk = (n - 1) / (p - 1), rest = (n - 1) % (p - 1);
		start = 0;

		for (int i = 1; i < p; i++)
		{
			if (rest > 0)
			{
				end = start + chunk + 1;
				rest--;
			}
			else
			{
				end = start + chunk;
			}

			int digit = 0;
			if (end <= N1)
			{
				for (int i = start; i < end; i++)
				{
					file_Numar1 >> digit;
					insert(number1, n, digit);
				}
			}
			else
			{
				for (int i = start; i < N1; i++)
				{
					file_Numar1 >> digit;
					insert(number1, n, digit);
				}
				for (int i = N1; i < end; i++)
					number1[i] = 0;
			}
			if (end <= N2)
			{
				for (int i = start; i < end; i++)
				{
					file_Numar2 >> digit;
					insert(number2, n, digit);
				}
			}
			else
			{
				for (int i = start; i < N2; i++)
				{
					file_Numar2 >> digit;
					insert(number1, n, digit);
				}
				for (int i = N2; i < end; i++)
					number2[i] = 0;
			}

			MPI_Send(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

			MPI_Send(number1 + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(number2 + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);

			start = end;
		}

		for (int i = 1; i < p; i++)
		{
			MPI_Recv(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			MPI_Recv(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			MPI_Recv(result + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
		}

		MPI_Recv(&n, 1, MPI_INT, p - 1, 0, MPI_COMM_WORLD, &status);

		writeNumber("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab3\\Varianta1\\Varianta1\\Varianta1\\Numar3.txt", result, n);

		auto endTime = high_resolution_clock::now();

		cout << duration<double, milli>(endTime - startTime).count();
	}
	else
	{
		// procesul id = 1 nu primeste carry - il considera egal 0
		int carry = 0;
		if (rank != 1)
			MPI_Recv(&carry, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);

		MPI_Recv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

		MPI_Recv(number1 + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(number2 + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

		//3. procesele fac suma cifrelor primite si calculeaza “report” (carry) corespunzator
		for (int i = start; i < end; i++)
		{
			int res = number1[i] + number2[i] + carry;
			result[i] = res % 10;
			carry = res / 10;
		}

		if (rank == p - 1)
		{
			if (carry != 0)
			{
				result[N - 1] = carry;
				end++;
			}
			else 
			{
				n--;
			}
		}
		
		//4. fiecare proces (cu exceptia ultimului) trimit “reportul” la procesul urmator care il foloseste pentru actualizarea rezultatului
		if (rank != p - 1)
		{
			MPI_Send(&carry, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
		}

		MPI_Send(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(result + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD);

		if (rank == p - 1)
			MPI_Send(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}