// 1. Generate 10000, 100000, and 1 million (1,000,000) random integer numbers
// (ranging from 0 to 9999) for running the sorting.
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int lower = 0, upper = 9999, count = 1, amount = 10000;
    int gen_num[amount];
    int check = 0;

    // set the starting value for the series of random ints
    srand(time(0));

    #pragma omp parallel num_threads(4)
    {  
        // random for {amount} ea
        for(int i = 0; i < amount; i++) {
            gen_num[i] = (rand() % (upper - lower + 1)) + lower;
            check += 1;
            printf("gen_num[%d]: %d\n", i, gen_num[i]);
        }
        printf("%d", check);
    }
}