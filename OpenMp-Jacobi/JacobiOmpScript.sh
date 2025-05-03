#!/bin/bash

# Nombre del archivo donde se guardarán los tiempos de ejecución
outputFile="ResultadoJacobiOmp.csv" # si se usa JacobiOmpScriptAll se debe cambiar por outputFile=$1

# Ubicación del ejecutable
executable="./JacobiExecutableOmp"

# Limpiar el archivo de salida antes de empezar las pruebas
echo "Tamaño,Steps,Hilos,Tiempos" > "$outputFile"

# Valores de nsteps y tamaños de malla a probar
nsteps_values=(500 800 1000 2000 3000 4000 4500 5000 6000 6500)
sizes=(100000 500000 2000000 3000000 5000000 6000000)
threads_values=(2 4 8 10)

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
            time=$(echo $output | awk -F',' '{print $2}')
            
            # Guardar el tiempo en el archivo en el formato solicitado
            echo "Tamaño: $size, Steps: $nsteps, Hilos: $threads, Tiempo: $time" >> "$outputFile"
        done
        echo " " >> "$outputFile"
    done
done

echo "Pruebas finalizadas."
