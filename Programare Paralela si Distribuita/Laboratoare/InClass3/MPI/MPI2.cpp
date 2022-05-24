#include "mpi.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	//int buf;
	//int rc, nr_procese, rank;
	//vector<int> nr1_local, nr2_local, res_local;
	//MPI_Status stare;
	//vector<int> nr1, nr2, rezultat;
	//int nr_elem;

	//rc = MPI_Init(NULL, NULL);
	//if (rc != MPI_SUCCESS) 
	//{
	//	cout << "Err init MPI";
	//	MPI_Abort(MPI_COMM_WORLD, rc);
	//}

	//MPI_Comm_size(MPI_COMM_WORLD, &nr_procese);
	//MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	////cout << "Proc "<<rank<<" din "<<nr_procese;
	//if (rank == 0) 
	//{
	//	//vector<int> nr1, nr2, rezultat;
	//	for (int i = 0; i < 10; i++)
	//	{
	//		nr1.push_back(i); nr2.push_back(i + 2);
	//	}

	//	// Aflam dimensiunea celui mai mare vector dintre cei doi operanzi (nr1 si nr2)
	//	int max = nr1.size() >= nr2.size() ? nr1.size() : nr2.size();
	//	rezultat.resize(max); // redimensionare vector rezultat la dimensiunea celui mai mare vector dintre nr1 si nr2

	//	//CALCUL nr_elem
	//	nr_elem = max / nr_procese;

	//	buf = 10;
	//	//exemplu folosire Bcast
	//	//MPI_Bcast(&buf, 1, MPI_INT, 0, MPI_COMM_WORLD);

	//	//Exemplu folosire Send si Recv
	//	for (int i = 1; i < nr_procese; i++) 
	//	{
	//		MPI_Send(&buf, 1, MPI_INT, i, 0, MPI_COMM_WORLD); //trimite la toate proc cu rank > 0 si rank < nr_procese
	//	}
	//	//cout << buf;
	//}
	//else 
	//{
	//	//buf = 2;
	//	//MPI_Bcast(&buf, 1, MPI_INT, 0, MPI_COMM_WORLD);
	//	MPI_Recv(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &stare);
	//	cout << buf;
	//}
	////MPI_Bcast(&buf, 1, MPI_INT, 0, MPI_COMM_WORLD);
	////cout << buf;

	//// GRESIT: aici nr1.size este cunoscut numai de procesul 0, celelalte nu au initializat vectorul nr1
	////int nr_elem = nr1.size() / nr_procese;

	////Trimitem nr_elemente prin BCast
	//MPI_Bcast(&nr_elem, 1, MPI_INT, 0, MPI_COMM_WORLD);

	////trebuie redimensionati vectorii locali
	//nr1_local.resize(nr_elem);
	//nr2_local.resize(nr_elem);
	//res_local.resize(nr_elem);
	//MPI_Scatter(nr1.data(), nr_elem, MPI_INT, nr1_local.data(), nr_elem, MPI_INT, 0, MPI_COMM_WORLD);
	//MPI_Scatter(nr2.data(), nr_elem, MPI_INT, nr2_local.data(), nr_elem, MPI_INT, 0, MPI_COMM_WORLD);
	////Sumare vectori
	//for (int i = 0; i < nr_elem; i++) 
	//{
	//	res_local[i] = nr1_local[i] + nr2_local[i];
	//}

	//MPI_Gather(res_local.data(), nr_elem, MPI_INT, rezultat.data(), nr_elem, MPI_INT, 0, MPI_COMM_WORLD);

	////In procesul root (=0) afisam rezultatul
	//if (rank == 0)
	//{
	//	for (int i = 0; i < 10; i++)
	//	{
	//		cout << rezultat[i] << "; ";
	//	}
	//}

	//MPI_Finalize();
	int nprocs, myrank;
	MPI_Init(NULL, NULL);
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	printf("Salutari de la %d", myrank);
	MPI_Finalize();
	printf("Program finalizat cu succes!");
	return 0;
}