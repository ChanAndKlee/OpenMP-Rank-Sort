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
struct timeval stop, start;

void sequentialRankSort(struct timeval timer, int *arr, int *sorted, int arraySize, int i, int j)
{
    gettimeofday(&start, NULL);
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
    gettimeofday(&stop, NULL);
}

int main(int argc, char *argv[])
{
    // If argument counter is not equal to 3, then display here
    if (argc != 3)
    {
        printf("./filename <arraySizeToSort> <number of threads>\n");
        return 1;
    }

    int arraySize, numThreads, threshold;

    // Convert argv[1], argv[2] to integers using atoi() to do Integer conversion
    arraySize = atoi(argv[1]);
    numThreads = atoi(argv[2]);

    double openmp_start, openmp_end;

    int i, j;
    int int_max = 10000; // define ranging from 0 - 9999

    int arr[1000000]; // array to be sorted
    int sorted[1000000];

    // Random the number
    for (i = 0; i < arraySize; i++)
    {
        arr[i] = rand() % int_max;
    }

    printf("> It's loading, pls wait\n");

    // Sequential rank sort
    if (numThreads == 1)
    {
        struct timeval timer;
        sequentialRankSort(timer, arr, sorted, arraySize, i, j);
        for (i = 0; i < arraySize; i++)
        {
            printf("unsorted : %d, sorted : %d\n", arr[i], sorted[i]);
        }
        printf(">> Time used in sequential rank sort : %f seconds\n", (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000000.0f);
        return 0;
    }

    srand(time(NULL));

    printf("Set threshold (0 for default): ");
    scanf("%d", &threshold);

    // Parallel Rank sort using OpenMP
    openmp_start = omp_get_wtime();

    omp_set_num_threads(numThreads);

    // Rank sort with OpenMP
    if (threshold < 1)
    {
        #pragma omp parallel for private(j)
        for (i = 0; i < arraySize; i++)
        {
            int x = 0;
            // printf("Thread %d is running number %d\n", omp_get_thread_num(), i);
            for (j = 0; j < arraySize; j++)
            {
                if (arr[j] < arr[i] || (arr[j] == arr[i] && j < i))
                    x++;
            }
            sorted[x] = arr[i];
        }
    } else {
        #pragma omp parallel for schedule(static, threshold) private(j)
        for (i = 0; i < arraySize; i++)
        {
            int x = 0;
            // printf("Thread %d is running number %d\n", omp_get_thread_num(), i);
            for (j = 0; j < arraySize; j++)
            {
                if (arr[j] < arr[i] || (arr[j] == arr[i] && j < i))
                    x++;
            }
            sorted[x] = arr[i];
        }
    }

    openmp_end = omp_get_wtime();

    for (i = 0; i < arraySize; i++)
    {
        printf("unsorted : %d, sorted : %d\n", arr[i], sorted[i]);
    }

    printf(">> Time used in parallel rank sort using OpenMP : %f seconds\n", openmp_end - openmp_start);
    return 0;
}