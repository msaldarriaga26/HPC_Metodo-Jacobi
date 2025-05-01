#!/bin/bash

# Nombre del archivo donde se guardarán los tiempos de ejecución
outputFile="resultadoJacobiSecuencial.csv" # si se usa JacobiSecuencialScriptAll se debe cambiar por outputFile=$1

# Ubicación del ejecutable
executable="./jacobiSecuencialExe"

# Limpiar el archivo de salida antes de empezar las pruebas
echo "Tamaño,Steps,Tiempos" > "$outputFile"

# Valores de nsteps y tamaños de malla a probar
nsteps_values=(100 500 1000 2000 3000 4000 5000 6000 8000 10000)
sizes=(100000 500000 2000000 3000000 5000000 7000000 10000000)

# Bucle para diferentes tamaños de malla y nsteps
for nsteps in "${nsteps_values[@]}"
do
    for size in "${sizes[@]}"
    do
        echo -n "Tamaño: $size, Steps: $nsteps, " >> "$outputFile"
        
        # Ejecutar el programa y capturar solo el tiempo de ejecución
        output=$($executable $size $nsteps)
        
        # Extraer el tiempo con awk y agregarlo a la salida
        time=$(echo $output | awk -F',' '{print $2}')
        
        # Guardar el tiempo en el archivo
        echo "Tiempo: $time" >> "$outputFile"
    done
    echo " " >> "$outputFile"
done

echo "Pruebas finalizadas."
