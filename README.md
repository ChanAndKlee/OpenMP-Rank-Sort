# OpenMP-Rank-Sort

This work is associated with the ITCS443 Parallel and Distributed Systems subject, the topic is "Parallel RankSort via OpenMP" to do the parallel sorting algorithm with different numbers of arrays and threads (which can be received from the command line)

## Members (Section 2)
6388030 Kulawut Makkamoltham  
6388040 Ariya   Phengphon 

## How to run the code
**Prerequisite:** The program is required to run on the **Windows Subsystem For Linux (WSL)**

**Detail:**
- There are 2 main versions: `main.c` and `optimized.c` (The given example on the README file will be `main.c`, but how to run is exactly the same, just change the naming file.)
- When the sample size is become larger, even it has more threads, but the running time takes to long to complete the work, therefore `optimized.c` will have a little code modification to let it run the inner loop parallely.

1. First, open the file name `main.c`, and run on the terminal by typing the following command to execute the file, then if you see the main.exe, it's a good sign to do the step 2

```shell
> gcc -fopenmp -o main main.c
```

2. Next, continue typing the following command to specify the `<arraySizeToSort>` and `<number of threads>` respectively.  
- **Example 1:** If the `<number of threads> = 0`, then the program will automatically run the sequential rank sort. ( 0 is just an option to run sequentially)   
- **Example 2:** Otherwise, if `<number of threads> >= 1`, it will ask for the ```threshold``` that will divide the data chunk size with the given threshold. For an example, if the threshold is 1000, the program will divide the chunk size into 1000 for each thread. ( or if in case that the threshold is 0, the program will divide the chunk size with using a default method )

**Example 1:** The example is when the user input **10000 random integer numbers sequentially.**
```shell
> ./main 10000 0
```

**Example 2:** The example is when the user input **10000 random integer numbers and 8 threads parallely with the threshold equal to 0**
```shell
> ./main 10000 8
> Set threshold (0 for default): 0
```


3. Once the user hit the enter the output will be shown on the terminal (it might take a longer time to compile when the chunk size is bigger), this is the following output of the above command

## Example of the output

**Example 1:** The example is when the user input **10000 random integer numbers sequentially.**
```
unsorted : 292, sorted : 9997
unsorted : 9307, sorted : 9999
unsorted : 9430, sorted : 9999
>> Time used in sequential rank sort : 0.392559 seconds
```

**Example 2:** The example is when the user input **10000 random integer numbers and 8 threads parallely with the threshold equal to 0**
```
unsorted : 292, sorted : 9997
unsorted : 9307, sorted : 9999
unsorted : 9430, sorted : 9999
>> Time used in parallel rank sort using OpenMP : 0.073546 seconds
```

