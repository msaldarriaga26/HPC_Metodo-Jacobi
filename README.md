
# Jacobi Project: Solving the 1D Poisson Equation

This project implements the Jacobi method to solve the 1D Poisson equation using four approaches: sequential, multithreading (threads), OpenMP and multiprocessing. The code is written in C and allows you to compare the performance of each approach in terms of execution times under different grid size and iteration configurations.

## Description

The purpose of this project is to solve the 1D Poisson equation using the iterative Jacobi method. The project allows the Jacobi algorithm to be executed in different parallelism configurations:

- **Sequential**: The algorithm runs on a single execution thread.
- **Multithreading**: Uses multiple threads to divide the work of solving the system.
- **Multiprocessing**: Uses multiple processes to perform the iterations in parallel.
- **Multithreading with OpenMP**: This version parallelizes the Jacobi method using OpenMP to further optimize performance, especially on multi-core machines.

Each version is optimized to evaluate efficiency based on the number of threads or processes used.

## Installation

1. To compile the code, you can use `make` or compile directly with `gcc`. Here's an example of how to do it for the sequential version:
   ```bash
   gcc -o JacobiSecuencial JacobiSecuencial.c -lm
   ```

   For the multithreading version:
   ```bash
   gcc -o JacobiHilos JacobiHilos.c -pthread -lm
   ```

   And for the multiprocessing version:
   ```bash
   gcc -o JacobiProcesos JacobiProcesos.c -lm
   ```
   For the OpenMP version (multithreading with OpenMP):
   ```bash
   gcc -fopenmp -o JacobiOmp JacobiOmp.c -lm
   ```

## Usage

To run the program, use the following commands. In each command, you can specify the grid size, number of iterations, and (if applicable) the number of threads or processes:

### Sequential Version:
```bash
./JacobiSecuencial <size> <iterations> <output_file>
```

### Multithreading Version:
```bash
./JacobiHilos <size> <iterations> <threads> <output_file>
```

### Multiprocessing Version:
```bash
./JacobiProcesos <size> <iterations> <processes> <output_file>
```

### Multithreading Version with OpenMP:
```bash
./JacobiOmp <size> <iterations> <threads> <output_file>
```

#### Parameters:
- `<size>`: Number of points in the grid (grid size).
- `<iterations>`: Number of iterations to perform.
- `<threads>` or `<processes>`: Number of threads or processes to use (only applies to multithreading or multiprocessing versions).
- `<output_file>`: The file where results will be saved (optional).

## Example Execution

### With Threads:
```bash
./JacobiHilos 100000 1000 4 results_threads.csv
```

### With Processes:
```bash
./JacobiProcesos 100000 1000 4 results_processes.csv
```

### Sequential:
```bash
./JacobiSecuencial 100000 1000 results_sequential.csv
```

### With OpenMP (Threads):
```bash
./JacobiOmp 100000 1000 4 results_openmp.csv
```

## Running Scripts

In addition to running the compiled versions of the code, you can run the `*.sh` scripts that are available to facilitate testing with different configurations. The scripts for each version are available in the following files:

- `JacobiHilosScript.sh`
- `JacobiProcesosScript.sh`
- `JacobiSecuencialScript.sh`
- `JacobiSecuencialScriptAll.sh`
- `JacobiOmpScript.sh`
- `JacobiOmpScriptAll.sh`

To run a script, use the following command:

```bash
bash <script_name>.sh
```

These scripts handle running multiple tests with different grid sizes, iteration counts, and numbers of threads/processes, and save the results to CSV files.

## Results

The program generates a CSV file with the results of each execution. The file contains the following fields:

- **Size**: The number of points in the grid.
- **Steps**: The number of iterations.
- **Threads/Processes**: The number of threads or processes used (depending on the version).
- **Time**: The execution time in seconds.
