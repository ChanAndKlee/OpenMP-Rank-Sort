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
#include <math.h>
#include <sys/time.h>

#define arraySize 10000 // define an array size to be sorted (e.g., 10000(4) , 100000(5) , 1000000(6) or 1M)
#define numThreads 8    // define number of threads (e.g., 1, 4, 8, 12, and 16)

int main()
{

    double openmp_start, openmp_end;
    struct timeval stop, start;

    int i, j;
    int int_max = 10000;    // define ranging from 0 - 9999

    int arr[arraySize]; // array to be sorted
    int sorted[arraySize];
    int linearlySorted[arraySize];
    int rank[arraySize];

    printf("> It's loading, pls wait\n");

    srand(time(NULL));

    /*
     * Random the number
     */
    for (i = 0; i < arraySize; i++)
    {
        arr[i] = rand() % int_max;
    }

    /*
     * Sequential Rank Sort
     */
    gettimeofday(&start, NULL);

    for (i = 0; i < arraySize; i++)
    {
        rank[i] = 0;
    }

    for (i = 0; i < arraySize; i++)
    {
        for (j = 0; j < arraySize; j++)
        {
            if (arr[j] < arr[i] || (arr[j] == arr[i] && j < i))
            {
                rank[i]++;
            }
        }
    }

    for (i = 0; i < arraySize; i++)
    {
        linearlySorted[rank[i]] = arr[i];
    }

    gettimeofday(&stop, NULL);

    /*
     * Parallel Rank sort using OpenMP
     */
    openmp_start = omp_get_wtime();

    for (i = 0; i < arraySize; i++)
    {
        rank[i] = 0;
    }

    omp_set_num_threads(numThreads);

    /*
     * Rank sort with OpenMP
     */
    #pragma omp parallel for private(j)
    for (i = 0; i < arraySize; i++)
    {
        for (j = 0; j < arraySize; j++)
        {
            if (arr[j] < arr[i] || (arr[j] == arr[i] && j < i))
            {
                rank[i]++;
            }
        }
    }

    for (i = 0; i < arraySize; i++)
    {
        sorted[rank[i]] = arr[i];
    }

    openmp_end = omp_get_wtime();

    for (i = 0; i < arraySize; i++)
    {
        printf("unsorted : %d, Parallel sorted : %d, Sequential sorted : %d\n", arr[i], sorted[i], linearlySorted[i]);
    }

    printf(">> Time used in parallel rank sort using openmp : %f seconds\n", openmp_end - openmp_start);
    printf(">> Time used in sequential rank sort : %f seconds\n", (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000000.0f);
    // Change this to print the Speed up
    // printf(">> Time Difference between parallel vs sequential rank sort : %f\n", fabs(difftime(seq_end, seq_start) - (openmp_end - openmp_start)));
    // 
    return 0;
}
