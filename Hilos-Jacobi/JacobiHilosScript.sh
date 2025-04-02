#!/bin/bash

# Nombre del archivo donde se guardarán los tiempos de ejecución
outputFile="resultadoJacobiHilos.csv"

# Ubicación del ejecutable
executable="./jacobiHilosExe"

# Limpiar el archivo de salida antes de empezar las pruebas
echo "Tamaño,Steps,Hilos,Tiempos" > "$outputFile"

# Valores de nsteps y tamaños de malla a probar
nsteps_values=(100 500 1000 2000 3000 4000 5000 6000 8000 10000)
sizes=(100000 500000 2000000 3000000 5000000 7000000 10000000)
threads_values=(2 4 8 16 32)

# Bucle para realizar todas las pruebas para un número de hilos
for threads in "${threads_values[@]}"
do
    echo "Iteración con $threads hilos" >> "$outputFile"
    
    # Bucle para diferentes tamaños de malla y nsteps
    for nsteps in "${nsteps_values[@]}"
    do
        for size in "${sizes[@]}"
        do
            # Ejecutar el programa y capturar solo el tiempo de ejecución
            output=$($executable $size $nsteps $threads)
            
            # Extraer el tiempo con awk y agregarlo a la salida
            time=$(echo $output | awk -F',' '{print $3}')
            
            # Guardar el tiempo en el archivo en el formato solicitado
            echo "Tamaño: $size, Steps: $nsteps, Hilos: $threads, Tiempo: $time" >> "$outputFile"
        done
        echo " " >> "$outputFile"
    done
done

echo "Pruebas finalizadas."
