# OpenMP-Rank-Sort

This work is associated with the ITCS443 Parallel and Distributed Systems subject, the topic is "Parallel RankSort via OpenMP" to do the parallel sorting algorithm with different numbers of arrays and threads (which can be received from the command line)

## Members (Section 2)
6388030 Kulawut Makkamoltham  
6388040 Ariya   Phengphon 

## How to run the code
1. First, open the file name `main.c`, and run on the terminal by typing the following command to execute the file, then if you see the main.exe, it's a good sign to do the step 2

```cmd
> gcc -fopenmp -o main main.c
```

2. Next, continue typing the following command to specify the `<arraySizeToSort>` and `<number of threads>` respectively.  
The example is when the user input **10000 random integer numbers and 4 threads parallelly.**

```cmd
> ./main 10000 4
```

3. Once the user hit the enter the output will be shown on the terminal (it might take a longer time to compile in some cases), it will show unsorted number, parallel sorted, and sequential sorted in order. On the last line, it will print the time spent in both parallel and sequential sort (using OpenMP) to be used when calculating the speedup (sequential/parallel).

## Example of the output

```
// This is just some parts of the output (since it's too long)
unsorted : 2242, Parallel sorted : 9988, Sequential sorted : 9988
unsorted : 2432, Parallel sorted : 9988, Sequential sorted : 9988
unsorted : 3527, Parallel sorted : 9988, Sequential sorted : 9988
unsorted : 7503, Parallel sorted : 9996, Sequential sorted : 9996
unsorted : 1887, Parallel sorted : 9997, Sequential sorted : 9997
unsorted : 5290, Parallel sorted : 9997, Sequential sorted : 9997
unsorted : 2565, Parallel sorted : 9997, Sequential sorted : 9997
unsorted : 4913, Parallel sorted : 9999, Sequential sorted : 9999
>> Time used in parallel rank sort using OpenMP : 0.110000 seconds
>> Time used in sequential rank sort : 0.350079 seconds
>> Speed Up (sequential / parallel) : 0.314214
```
