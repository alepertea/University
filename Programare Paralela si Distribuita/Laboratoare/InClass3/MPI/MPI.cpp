#include <iostream>
#include <vector>
#include "mpi.h"

using namespace std;

int main()
{
    int numProcesses, rank, a = 3;

    int rc = MPI_Init(NULL, NULL);
    if (rc != MPI_SUCCESS)
    {
        cout << "Error MPI_Init";
        MPI_Abort(MPI_COMM_WORLD, rc);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

//    cout << "Process " << rank << " of " << numProcesses;

    if (rank == 0)
        a = 10;
    cout << "Before barrier: process " << rank << ": " << a << endl;

    MPI_Barrier(MPI_COMM_WORLD);

    cout << "After barrier: process " << rank << ": " << a << endl;

    MPI_Bcast(&a, 1, MPI_INT, 0, MPI_COMM_WORLD); // procesul 0 cand ajunge aici, trimite; celelalte asteapta pana cand primesc informatia si doar apoi pleaca mai departe
    cout << "After bcast: process " << rank << ": " << a;

    if (rank == 0)
    {
        int a = 2; // variabila creata numai in memoria procesului 0
        //cout << a;
        //MPI_Send();
    }
    else
    {
        //cout << a;
        //MPI_Recv();

    }

    MPI_Finalize();

    return 0;
}
