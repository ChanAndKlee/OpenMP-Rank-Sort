// # ================================================= #
// #    Project name: Parallel Ranksort via OpenMP     #
// #               (Section 2)                         #
// #   6388030  Kulawut     Makkamoltham               #
// #   6388040  Ariya       Phengphon                  #
// # ================================================= #

// REF: https://github.com/tebesfinwo/CISC-4335-OpenMP-Rank-Sort-/blob/master/Parallel%20Rank%20Sort/main.c

#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    // If argument counter is not equal to 3, then display here
    if(argc != 3) {
        printf("./filename <arraySizeToSort> <number of threads>\n");
    }

    int arraySize, numThreads;
    
    // Convert argv[1], argv[2] to integers using atoi() to do Integer conversion
    arraySize = atoi(argv[1]);
    numThreads = atoi(argv[2]);

    double openmp_start, openmp_end;
    struct timeval stop, start;

    int i, j;
    int int_max = 10000;    // define ranging from 0 - 9999

    int arr[arraySize];     // array to be sorted
    int sorted[arraySize];
    int linearlySorted[arraySize];

    printf("> It's loading, pls wait\n");

    srand(time(NULL));

    // Random the number
    for (i = 0; i < arraySize; i++)
    {
        arr[i] = rand() % int_max;
    }

    // Sequential Rank Sort
    gettimeofday(&start, NULL);
    for (i = 0; i < arraySize; i++)
    {
        int x = 0;
        for (j = 0; j < arraySize; j++)
        {
            if (arr[j] < arr[i] || (arr[j] == arr[i] && j < i))
                x++;
        }
        linearlySorted[x] = arr[i];
    }

    gettimeofday(&stop, NULL);

    // Parallel Rank sort using OpenMP
    openmp_start = omp_get_wtime();

    omp_set_num_threads(numThreads);

    // Rank sort with OpenMP
    #pragma omp parallel for private(j)
    for (i = 0; i < arraySize; i++)
    {
        int x = 0;
        for (j = 0; j < arraySize; j++)
        {
            if (arr[j] < arr[i] || (arr[j] == arr[i] && j < i))
                x++;
        }
        sorted[x] = arr[i];
    }

    openmp_end = omp_get_wtime();

    for (i = 0; i < arraySize; i++)
    {
        printf("unsorted : %d, Parallel sorted : %d, Sequential sorted : %d\n", arr[i], sorted[i], linearlySorted[i]);
    }

    printf(">> Time used in parallel rank sort using OpenMP : %f seconds\n", openmp_end - openmp_start);
    printf(">> Time used in sequential rank sort : %f seconds\n", (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000000.0f);
    printf(">> Speed Up (sequential / parallel) : %f\n", (openmp_end - openmp_start) / ((stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000000.0f) );
    return 0;
}