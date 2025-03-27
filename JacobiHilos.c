#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// Global variables
double *u, *f, *utmp;

struct thread_info { 
    int from;  // Start index for the thread
    int to;    // End index for the thread
    double h2; // The square of the step size
};

// Thread subroutine for the Jacobi method
void *thread_subroutine(void *threadarg) {
    struct thread_info *thread_info = (struct thread_info *)threadarg;
    int from = thread_info->from;
    int to = thread_info->to;
    double h2 = thread_info->h2;

    // Perform the calculations using the given indices
    for (int i = from; i < to; ++i) {
        utmp[i] = (u[i - 1] + u[i + 1] + h2 * f[i]) / 2;
    }

    // Updating u with new values from utmp
    for (int i = from; i < to; ++i) {
        u[i] = (utmp[i - 1] + utmp[i + 1] + h2 * f[i]) / 2;
    }

    pthread_exit(NULL);
}

// Main function for the Jacobi method
void jacobi(int nsweeps, int size, int threads_ammount) {
    double h = 1.0 / size;
    double h2 = h * h;

    struct thread_info threads_info[threads_ammount];
    pthread_t threads[threads_ammount];

    // Initialize boundary conditions
    utmp[0] = u[0];
    utmp[size] = u[size];

    // Perform the iterations
    for (int sweep = 0; sweep < nsweeps; sweep += 2) {
        // Create threads and initialize their data
        for (int thread_idx = 0; thread_idx < threads_ammount; thread_idx++) {
            threads_info[thread_idx].h2 = h2;
            threads_info[thread_idx].from = thread_idx * (size - 1) / threads_ammount;
            threads_info[thread_idx].to = (thread_idx + 1) * (size - 1) / threads_ammount;

            // Set boundaries for first thread
            if (thread_idx == 0) {
                threads_info[thread_idx].from = 1;
            }

            // Create the thread
            if (pthread_create(&threads[thread_idx], NULL, thread_subroutine,
                               (void *)&threads_info[thread_idx])) {
                fprintf(stderr, "Error creating thread\n");
                exit(-1);
            }
        }

        // Join the threads and collect the results
        for (int thread_idx = 0; thread_idx < threads_ammount; thread_idx++) {
            if (pthread_join(threads[thread_idx], NULL)) {
                fprintf(stderr, "Error joining thread\n");
                exit(-1);
            }
        }
    }
}

// Function to write the solution to a file
void write_solution(int n, double *u, const char *fname) {
    FILE *fp = fopen(fname, "w+");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s\n", fname);
        return;
    }

    double h = 1.0 / n;
    for (int i = 0; i <= n; ++i) {
        fprintf(fp, "%g %g\n", i * h, u[i]);
    }
    fclose(fp);
}

int main(int argc, char **argv) {
    int n, nsteps, threads_ammount;
    char *fname;
    struct timeval tstart, tend;

    // Process input parameters
    n = (argc > 1) ? atoi(argv[1]) : 100;
    nsteps = (argc > 2) ? atoi(argv[2]) : 100;
    threads_ammount = (argc > 3) ? atoi(argv[3]) : 4;
    fname = (argc > 4) ? argv[4] : NULL;

    // Allocate memory for u, f, and utmp using calloc to initialize them to zero
    u = (double *)calloc(n + 1, sizeof(double));
    f = (double *)calloc(n + 1, sizeof(double));
    utmp = (double *)calloc(n + 1, sizeof(double));

    if (u == NULL || f == NULL || utmp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the source function (f)
    double h = 1.0 / n;
    for (int i = 0; i <= n; ++i) {
        f[i] = i * h;
    }

    // Start timer
    gettimeofday(&tstart, NULL);
    
    // Run the Jacobi method
    jacobi(nsteps, n, threads_ammount);
    
    // End timer
    gettimeofday(&tend, NULL);

    // Calculate execution time
    double exec_time = (tend.tv_sec - tstart.tv_sec) + 1e-6 * (tend.tv_usec - tstart.tv_usec);
    
    printf("%d,%d,%f\n", n, threads_ammount, exec_time);

    // Write the solution to a file if provided
    if (fname) {
        write_solution(n, u, fname);
    }

    // Free allocated memory
    free(f);
    free(u);
    free(utmp);

    return 0;
}
