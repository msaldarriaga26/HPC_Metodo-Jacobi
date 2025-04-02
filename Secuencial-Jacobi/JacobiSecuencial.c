#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// Función para inicializar el arreglo u con ceros
void initialize_array(double *arr, int n) {
    memset(arr, 0, (n + 1) * sizeof(double));
}

// Función para configurar la fuente (f)
void set_source(double *f, int n, double h) {
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

    for (sweep = 0; sweep < nsweeps; sweep += 2) {
        // Old data in u; new data in utmp
        for (i = 1; i < n; ++i) {
            utmp[i] = (u[i - 1] + u[i + 1] + h2 * f[i]) / 2;
        }

        // Old data in utmp; new data in u
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
    int n, nsteps;
    double *u, *f, h;
    char *fname;
    struct timeval tstart, tend;

    // Procesar los argumentos de entrada
    n = (argc > 1) ? atoi(argv[1]) : 100;
    nsteps = (argc > 2) ? atoi(argv[2]) : 100;
    fname = (argc > 3) ? argv[3] : NULL;
    h = 1.0 / n;

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
