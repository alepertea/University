// OpenMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    int a = 1, b = 2, c = 3, d;
    int is_parallel = 1;

#pragma omp parallel if (is_parallel == 1) num_threads(8) private(a) shared(b) firstprivate(c) private(d)
    {
        d = omp_get_thread_num();
        cout << d << endl;
    }
    //int x = 2;
    //int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    //int b[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    //int c[10];

    ////cout << x;
    ////printf("1 - %d\n", x);
    //omp_set_num_threads(3);

    ////cout << omp_get_num_threads() << endl;
    //printf("1 - %d - %d\n", x, omp_get_thread_num());

    //#pragma omp parallel shared(a, b, c) private(x)
    //{
    //    x = 10;
    //    //cout << omp_get_num_threads() << endl;
    //    //cout << x << endl;      // va fi rupt

    ////#pragma omp for schedule(guided, 3) nowait
    ////    for (int i = 0; i < 10; i++)
    ////    {
    ////        c[i] = a[i] + b[i];
    ////        printf("2 - %d - %d\n", i, omp_get_thread_num());
    ////    }
    ////    printf("final for\n");
    ////
    ////} // join

    //#pragma omp sections
    //{
    //    #pragma omp section
    //    {
    //        printf("Section 1 - %d\n", omp_get_thread_num());
    //    }
    //    #pragma omp section
    //    {
    //        printf("Section 2 - %d\n", omp_get_thread_num());
    //    }
    //    #pragma omp section
    //    {
    //        printf("Section 3 - %d\n", omp_get_thread_num());
    //    }
    //}

    //    printf("3 - %d - %d\n", x, omp_get_thread_num());
    //    return 0;
    //}

    //#pragma omp critical
    //{
    //    printf("Critical - %d\n", omp_get_thread_num());
    //}

    //#pragma omp master
    //{
    //    printf("Master - %d\n", omp_get_thread_num());
    //}
}