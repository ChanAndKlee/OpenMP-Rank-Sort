/**
 *
 * @author Jun Han ( Johnson  )  Ooi
 * CISC 4335
 * Parallel Rank Sort
 *
 * Created on : April 30th 2014
 * Modified on : May 2nd 2014
 *
 * */
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>

#define arraySize 10
#define numThreads 8

int main()
{
    // Time Variables
    double openmp_start, openmp_end;
    struct timeval stop, start;

    // Looping Variables
    int i, j;

    // Array for storing elements
    static int arr[arraySize]; // array to be sorted
    static int sorted[arraySize];
    static int linearlySorted[arraySize];

    srand(time(NULL));

    for (i = 0; i < arraySize; i++)
    {
        arr[i] = rand() % 10000;
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
    // Parallel Rank sort using Openmp
    openmp_start = omp_get_wtime();

    omp_set_num_threads(numThreads);

    // Rank sort with openmp
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
        printf("unsorted : %d, Parallel sorted : %d, Sequential sorted : %d  \n", arr[i], sorted[i], linearlySorted[i]);
    }

    printf("Time used in parallel rank sort using openmp : %.7f seconds \n", openmp_end - openmp_start);
    printf("Time used in sequential rank sort : %.7f seconds \n ", (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000000.0f);

    return 0;
}
