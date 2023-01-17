# parallel-merge-sort-mpi
My implementation of Merge Sort algorithm in C++ using MPI library for paralleling.

## Instruction
### Sequential
```
./sequential.exe <YOUR SIZE OF ARRAY>

# Example:
./sequential.exe 1000000
```


### Parallel
```
mpiexec -n <YOUR NUM OF PROCESSES> ./main.exe <YOUR SIZE OF ARRAY>

# Example:
mpiexec -n 4 ./main.exe 1000000
```

### All-In-One
```
./run_test.sh
```