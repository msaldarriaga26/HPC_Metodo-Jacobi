#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>  // Incluir OpenMP

// Función para inicializar el arreglo u con ceros
void initialize_array(double *arr, int n) {
    memset(arr, 0, (n + 1) * sizeof(double));
}

// Función para configurar la fuente (f)
void set_source(double *f, int n, double h) {
    #pragma omp parallel for
    for (int i = 0; i <= n; ++i) {
        f[i] = i * h;
    }
}

// Función de Jacobi
void jacobi(int nsweeps, int n, double *u, double *f) {
    int i, sweep;
    double h = 1.0 / n;
    double h2 = h * h;
    double *utmp = (double *)malloc((n + 1) * sizeof(double));
    
    if (utmp == NULL) {
        fprintf(stderr, "Error al asignar memoria para utmp\n");
        return;
    }

    // Inicializar las condiciones de frontera
    utmp[0] = u[0];
    utmp[n] = u[n];

    // Paralelización del ciclo de barrido
    for (sweep = 0; sweep < nsweeps; sweep += 2) {
        // Old data in u; new data in utmp
        #pragma omp parallel for
        for (i = 1; i < n; ++i) {
            utmp[i] = (u[i - 1] + u[i + 1] + h2 * f[i]) / 2;
        }

        // Old data in utmp; new data in u
        #pragma omp parallel for
        for (i = 1; i < n; ++i) {
            u[i] = (utmp[i - 1] + utmp[i + 1] + h2 * f[i]) / 2;
        }
    }

    free(utmp);
}

// Función para escribir la solución en un archivo
void write_solution(int n, double *u, const char *fname) {
    FILE *fp = fopen(fname, "w+");
    if (fp == NULL) {
        fprintf(stderr, "Error al abrir el archivo %s\n", fname);
        return;
    }

    double h = 1.0 / n;
    for (int i = 0; i <= n; ++i) {
        fprintf(fp, "%g %g\n", i * h, u[i]);
    }
    fclose(fp);
}

int main(int argc, char **argv) {
    int n, nsteps, num_threads;
    double *u, *f, h;
    char *fname = NULL;
    struct timeval tstart, tend;

    // Procesar los argumentos de entrada
    if (argc < 4) {
        fprintf(stderr, "Uso incorrecto. El formato correcto es: ./JacobiExecutableOmp <n> <nsteps> <num_threads> [<output_file>]\n");
        return 1;
    }

    n = atoi(argv[1]);         // Tamaño de la malla
    nsteps = atoi(argv[2]);    // Número de pasos
    num_threads = atoi(argv[3]); // Número de hilos

    if (argc > 4) {
        fname = argv[4];  // Nombre del archivo de salida (opcional)
    }

    h = 1.0 / n;

    // Establecer el número de hilos con OpenMP
    omp_set_num_threads(num_threads);

    // Asignar memoria para los arreglos
    u = (double *)malloc((n + 1) * sizeof(double));
    f = (double *)malloc((n + 1) * sizeof(double));

    if (u == NULL || f == NULL) {
        fprintf(stderr, "Error al asignar memoria para los arreglos\n");
        return 1;
    }

    // Inicializar los arreglos
    initialize_array(u, n);
    set_source(f, n, h);

    // Ejecutar el solver
    gettimeofday(&tstart, NULL);
    jacobi(nsteps, n, u, f);
    gettimeofday(&tend, NULL);

    // Calcular el tiempo de ejecución
    double exec_time = (tend.tv_sec - tstart.tv_sec) + 1e-6 * (tend.tv_usec - tstart.tv_usec);
    printf("%d,%f\n", n, exec_time);

    // Si se especifica un nombre de archivo, guardar la solución
    if (fname) {
        write_solution(n, u, fname);
    }

    // Liberar memoria
    free(f);
    free(u);

    return 0;
}
