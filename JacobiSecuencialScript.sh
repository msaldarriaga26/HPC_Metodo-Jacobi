#!/bin/bash

# Nombre del archivo donde se guardarán los tiempos de ejecución
outputFile="resultadoJacobiSecuencial.csv"

# Ubicación del ejecutable de multiplicación de matrices
executable="./jacobiSecuencialExe"

# Limpiar el archivo de salida antes de empezar las pruebas
echo "Iteración,Tamaño,Tiempo" > "$outputFile"

# Bucle para ejecutar las pruebas múltiples veces
for j in {1..10}
do
    echo "Iteración $j" >> "$outputFile"
    
    # Bucle para diferentes tamaños de matrices
    for size in  5000 25000 50000 100000 150000 200000 250000
    do
        echo -n "Tamaño: $size," >> "$outputFile"
        
        # Ejecutar el programa y añadir el tiempo al archivo de salida
        $executable $size >> "$outputFile"
    done

    echo "" >> "$outputFile"

done

echo "Pruebas finalizadas."
