#!/bin/bash

# Nombre del archivo donde se guardarán los tiempos de ejecución
outputFile="resultadoJacobiProcesos.csv"

# Ubicación del ejecutable
executable="./jacobiProcesosExe"

# Limpiar el archivo de salida antes de empezar las pruebas
echo "Tamaño,Steps,Procesos,Tiempos" > "$outputFile"

# Valores de nsteps y tamaños de malla a probar
nsteps_values=(100 500 1000 2000 3000 4000 5000 6000 8000 10000)
sizes=(100000 500000 2000000 3000000 5000000 7000000 10000000)
processes_values=(2 4 8 16 32)

# Bucle para realizar todas las pruebas para diferentes números de procesos
for processes in "${processes_values[@]}"
do
    echo "Iteración con $processes procesos" >> "$outputFile"
    
    # Bucle para diferentes tamaños de malla y nsteps
    for nsteps in "${nsteps_values[@]}"
    do
        for size in "${sizes[@]}"
        do
            # Ejecutar el programa y capturar solo el tiempo de ejecución
            output=$($executable $size $nsteps $processes)
            
            # Extraer el tiempo con awk y agregarlo a la salida
            time=$(echo $output | awk -F',' '{print $3}')
            
            # Guardar el tiempo en el archivo en el formato solicitado
            echo "Tamaño: $size, Steps: $nsteps, Procesos: $processes, Tiempo: $time" >> "$outputFile"
        done
        echo " " >> "$outputFile"
    done
done

echo "Pruebas finalizadas."
