#!/bin/bash

# Nombre del archivo donde se guardarán los tiempos de ejecución
outputFile="resultadoJacobiHilos.csv"

# Ubicación del ejecutable
executable="./jacobiHilosExe"

# Limpiar el archivo de salida antes de empezar las pruebas
echo "Iteración,Tamaño,Hilos,Tiempo" > "$outputFile"

# Bucle para diferentes números de Hilos (2, 4, 8, 16, 32)
for numThreads in 2 4 8 16 32
do
    # Bucle para ejecutar las pruebas múltiples veces
    for j in {1..10}
    do
        echo "Iteración $j con $numThreads Hilos" >> "$outputFile"
        
        # Bucle para diferentes tamaños de matrices
        for size in 5000 25000 50000 100000 150000 200000 250000
        do
            echo -n "Tamaño: $size, Hilos: $numThreads," >> "$outputFile"
            
            # Ejecutar el programa y capturar solo el tiempo de ejecución
            output=$($executable $size $numThreads)
            
            # Si el tiempo está en la última columna, extraerlo con awk
            time=$(echo $output | awk -F',' '{print $3}')
            
            # Guardar el tiempo en el archivo
            echo "$time" >> "$outputFile"
        done

        # Añadir un salto de línea después de cada conjunto de iteraciones
        echo "" >> "$outputFile"

    done
done

echo "Pruebas finalizadas."
